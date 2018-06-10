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
  | Author:  ZiHang Gao <ocdoco@gmail.com>                               |
  +----------------------------------------------------------------------+
*/

/* $Id$ */

#ifndef PHP_XFILTER_H
#define PHP_XFILTER_H

/* datrie include */
#include <datrie/trie.h>

extern zend_module_entry xfilter_module_entry;
#define phpext_xfilter_ptr &xfilter_module_entry

#define PHP_XFILTER_VERSION "0.1.0" /* Replace with version number for your extension */

#define KEYWORD_MAX_LEN 1024

#ifdef PHP_WIN32
#	define PHP_XFILTER_API __declspec(dllexport)
#elif defined(__GNUC__) && __GNUC__ >= 4
#	define PHP_XFILTER_API __attribute__ ((visibility("default")))
#else
#	define PHP_XFILTER_API
#endif

#ifdef ZTS
#include "TSRM.h"
#endif

ZEND_BEGIN_MODULE_GLOBALS(xfilter)
  Trie *trie;
  char *filename;
ZEND_END_MODULE_GLOBALS(xfilter)

#define XFILTER_G(v) ZEND_MODULE_GLOBALS_ACCESSOR(xfilter, v)

#if defined(ZTS) && defined(COMPILE_DL_XFILTER)
ZEND_TSRMLS_CACHE_EXTERN()
#endif

#endif	/* PHP_XFILTER_H */

/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */
