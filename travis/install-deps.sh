#!/bin/sh

wget https://ftp.gnu.org/pub/gnu/libiconv/libiconv-1.7.tar.gz \
&& tar zxvf libiconv-1.7.tar.gz \
&& cd libiconv-1.7 && ./configure && make && make install && cd .. \

&& wget https://github.com/tlwg/libdatrie/releases/download/v0.2.11/libdatrie-0.2.11.tar.xz \
&& tar zxvf libdatrie-0.2.11.tar.xz \
&& cd libdatrie-0.2.11 && ./configure && make && make install
