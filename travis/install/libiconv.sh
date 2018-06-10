#!/bin/sh

wget https://ftp.gnu.org/pub/gnu/libiconv/libiconv-1.14.tar.gz \
&& tar zxvf libiconv-1.14.tar.gz \
&& cd libiconv-1.14 && ./configure && make && sudo make install
