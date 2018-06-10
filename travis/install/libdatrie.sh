#!/bin/sh

wget https://github.com/tlwg/libdatrie/releases/download/v0.2.11/libdatrie-0.2.11.tar.xz \
&& tar xvf libdatrie-0.2.11.tar.xz \
&& cd libdatrie-0.2.11 && ./configure LDFLAGS=-L/usr/local/lib LIBS=-liconv && make && make install
