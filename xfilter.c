/*
  +----------------------------------------------------------------------+
  | PHP Version 7                                                        |
  +----------------------------------------------------------------------+
  | Copyright (c) 1997-2018 The PHP Group                                |
  +----------------------------------------------------------------------+
  | This source file is subject to version 3.01 of the PHP license,      |
  | that is bundled with this package in the file LICENSE, and is        |
  | available through the world-wide-web at the following url:           |
  | http://www.php.net/license/3_01.txt                                  |
  | If you did not receive a copy of the PHP license and are unable to   |
  | obtain it through the world-wide-web, please send a note to          |
  | license@php.net so we can mail you a copy immediately.               |
  +----------------------------------------------------------------------+
  | Author:    ZiHang Gao <cdoco@gmail.com>                              |
  +----------------------------------------------------------------------+
*/

/* $Id$ */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "php.h"
#include "php_ini.h"
#include "ext/standard/info.h"
#include "php_xfilter.h"

zend_class_entry *xfilter_ce;

ZEND_DECLARE_MODULE_GLOBALS(xfilter)

static int xfilter_search(Trie *trie, const AlphaChar *text, zval *data)
{
	TrieState *s = NULL;
	const AlphaChar *p = NULL;
	const AlphaChar *base = NULL;
    zval word;

	base = text;
    if (!(s = trie_root(trie))) {
		return FAILURE;
    }

    while (*text) {
        p = text;
        if (!trie_state_is_walkable(s, *p)) {
            trie_state_rewind(s);
            text++;
            continue;
        }

        while (*p && trie_state_is_walkable(s, *p) && !trie_state_is_leaf(s)) {
            trie_state_walk(s, *p++);
            if (trie_state_is_terminal(s)) {
                array_init_size(&word, 3);
                add_next_index_long(&word, text - base);
                add_next_index_long(&word, p - text);
                add_next_index_zval(data, &word);
            }
        }
        trie_state_rewind(s);
        text++;
    }
    trie_state_free(s);

	return SUCCESS;
}

/* Construct. */
PHP_METHOD(xfilter, __construct)
{
	zend_string *filename = NULL;

	if (zend_parse_parameters(ZEND_NUM_ARGS(), "S", &filename) == FAILURE) {
        return;
    }

	if (ZSTR_LEN(filename) < 1 || strlen(ZSTR_VAL(filename)) != ZSTR_LEN(filename)) {
        php_error_docref(NULL, E_WARNING, "need to set the file path");
        RETURN_FALSE;
    }

	XFILTER_G(filename) = ZSTR_VAL(filename);
	RETURN_TRUE;
}

/* Save function */
PHP_METHOD(xfilter, save)
{
	zend_ulong i;
	zval *dirty_words = NULL, *value = NULL;

	if (zend_parse_parameters(ZEND_NUM_ARGS(), "a", &dirty_words) == FAILURE) {
        return;
    }

    ZEND_HASH_FOREACH_NUM_KEY_VAL(Z_ARRVAL_P(dirty_words), i, value) {
		AlphaChar alpha_key[KEYWORD_MAX_LEN+1];
		unsigned char *p = NULL;
		size_t i = 0;

		if (Z_TYPE_P(value) == IS_STRING) {
			/* Test length problem */
			if (Z_STRLEN_P(value) > KEYWORD_MAX_LEN || Z_STRLEN_P(value) < 1) {
				php_error_docref(NULL, E_WARNING, "keyword should has [1, %d] bytes", KEYWORD_MAX_LEN);
				RETURN_FALSE;
			}

			p = (unsigned char *)Z_STRVAL_P(value);

    		while (*p && *p != '\n' && *p != '\r') {
        		alpha_key[i++] = (AlphaChar)*p;
        		p++;
    		}

    		alpha_key[i] = TRIE_CHAR_TERM;
    		if (!trie_store(XFILTER_G(trie), alpha_key, -1)) {
        		RETURN_FALSE;
    		}
		} else {
			php_error_docref(NULL, E_WARNING, "keyword type should be string");
		}
    } ZEND_HASH_FOREACH_END();

	/* save file */
	if (trie_save(XFILTER_G(trie), XFILTER_G(filename))) {
        RETURN_FALSE;
    }

	RETURN_TRUE;
}

/* Search function */
PHP_METHOD(xfilter, search)
{
	zend_string *text = NULL;
	AlphaChar *alpha_text = NULL;
	size_t i;

	if (zend_parse_parameters(ZEND_NUM_ARGS(), "S", &text) == FAILURE) {
        return;
    }

	if (ZSTR_LEN(text) < 1) {
		php_error_docref(NULL, E_NOTICE, "input is empty");
		return;
	}

	if (trie_is_dirty(XFILTER_G(trie))) {
		XFILTER_G(trie) = trie_new_from_file(XFILTER_G(filename));
		if (!XFILTER_G(trie)) {
			php_error_docref(NULL, E_WARNING, "Unable to load %s", XFILTER_G(filename));
			return;
		}
	}

	array_init(return_value);
	alpha_text = emalloc(sizeof(AlphaChar) * (ZSTR_LEN(text) + 1));

	for (i = 0; i < ZSTR_LEN(text); i++) {
		alpha_text[i] = (AlphaChar)ZSTR_VAL(text)[i];
	}
	alpha_text[ZSTR_LEN(text)] = TRIE_CHAR_TERM;

	if (xfilter_search(XFILTER_G(trie), alpha_text, return_value)) {
		/* handle */
	}

	efree(alpha_text);
}

static const zend_function_entry xfilter_methods[] = {
    PHP_ME(xfilter, __construct, NULL, ZEND_ACC_CTOR | ZEND_ACC_PUBLIC)
    PHP_ME(xfilter, save, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(xfilter, search, NULL, ZEND_ACC_PUBLIC)
    PHP_FE_END
};

PHP_MINIT_FUNCTION(xfilter)
{
	AlphaMap *alpha_map;
	zend_class_entry ce;
    INIT_CLASS_ENTRY(ce, "Cdoco\\Filter", xfilter_methods);

    xfilter_ce = zend_register_internal_class(&ce);

	/* Init trie */
    alpha_map = alpha_map_new();
    if (!alpha_map) {
        return FAILURE;
    }

    if (alpha_map_add_range(alpha_map, 0x00, 0xff) != 0) {
        /* treat all strings as byte stream */
        alpha_map_free(alpha_map);
        return FAILURE;
    }

    XFILTER_G(trie) = trie_new(alpha_map);
    alpha_map_free(alpha_map);

    if (!XFILTER_G(trie)) {      
        return FAILURE;
    }

	return SUCCESS;
}

PHP_MSHUTDOWN_FUNCTION(xfilter)
{
	/* free */
	if (XFILTER_G(trie)) {
		trie_free(XFILTER_G(trie));
	}
	
	return SUCCESS;
}

PHP_MINFO_FUNCTION(xfilter)
{
	php_info_print_table_start();
	php_info_print_table_header(2, "xfilter support", "enabled");
	php_info_print_table_end();
}

/* GINIT */
PHP_GINIT_FUNCTION(xfilter)
{
    xfilter_globals->trie = NULL;
	xfilter_globals->filename = NULL;
}

zend_module_entry xfilter_module_entry = {
	STANDARD_MODULE_HEADER,
	"xfilter",
	NULL,
	PHP_MINIT(xfilter),
	PHP_MSHUTDOWN(xfilter),
	NULL,
	NULL,
	PHP_MINFO(xfilter),
	PHP_XFILTER_VERSION,
	PHP_MODULE_GLOBALS(xfilter),
    PHP_GINIT(xfilter),
    NULL,
    NULL,
    STANDARD_MODULE_PROPERTIES_EX
};

#ifdef COMPILE_DL_XFILTER
#ifdef ZTS
ZEND_TSRMLS_CACHE_DEFINE()
#endif
ZEND_GET_MODULE(xfilter)
#endif

/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */
