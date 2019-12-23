#!/bin/bash

gcc -o a $1 -lmysqlclient -I/usr/include/mysql -L/usr/lib/doc/ -lz `pkg-config --libs --cflags gtk+-2.0`
