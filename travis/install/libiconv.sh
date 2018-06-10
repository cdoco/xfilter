#!/bin/sh

wget https://ftp.gnu.org/pub/gnu/libiconv/libiconv-1.7.tar.gz \
&& tar zxvf libiconv-1.7.tar.gz \
&& cd libiconv-1.7 && ./configure && make && sudo make install
