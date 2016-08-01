SUBDIRS = src
dist_doc_DATA = README.md

AM_CPPFLAGS = -I$(abs_top_builddir)/src/include -I$(abs_top_builddir)/src/lib -L$(abs_top_builddir)/src/lib -std=c++11
export AM_CPPFLAGS

MAIN_LIBS = -lcrypto
export MAIN_LIBS
