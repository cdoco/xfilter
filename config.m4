dnl $Id$
dnl config.m4 for extension xfilter

PHP_ARG_WITH(xfilter, for xfilter support,
  [  --with-xfilter             Include xfilter support])

if test "$PHP_XFILTER" != "no"; then

  SEARCH_PATH="/usr/local /usr"
  SEARCH_FOR="/include/datrie/trie.h"
  if test -r $PHP_XFILTER/$SEARCH_FOR; then
    XFILTER_DIR=$PHP_XFILTER
  else
    AC_MSG_CHECKING([for xfilter files in default path])
    for i in $SEARCH_PATH ; do
      if test -r $i/$SEARCH_FOR; then
        XFILTER_DIR=$i
        AC_MSG_RESULT(found in $i)
      fi
    done
  fi

  if test -z "$XFILTER_DIR"; then
    AC_MSG_RESULT([not found])
    AC_MSG_ERROR([Please reinstall the libdatrie])
  fi

  PHP_ADD_INCLUDE($XFILTER_DIR/include)

  LIBNAME=datrie
  LIBSYMBOL=trie_new_from_file

  PHP_CHECK_LIBRARY($LIBNAME, $LIBSYMBOL,
  [
    PHP_ADD_LIBRARY_WITH_PATH($LIBNAME, $XFILTER_DIR/lib, XFILTER_SHARED_LIBADD)
    AC_DEFINE(HAVE_XFILTERLIB, 1, [libdatrie found and included])
  ],[
    AC_MSG_ERROR([wrong libdatrie version or lib not found])
  ],[
    -L$XFILTER_DIR/lib -ldatrie
  ])

  PHP_SUBST(XFILTER_SHARED_LIBADD)
  PHP_NEW_EXTENSION(xfilter, xfilter.c, $ext_shared)
fi
