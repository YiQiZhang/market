#!/bin/sh 

SEARCH_PATH=`pwd`

gdb server -d $SEARCH_PATH -d $SEARCH_PATH/../include
