# config-lib.mk -- include file for Makefile to prepare
# the environment to handle configuration parameters.
# Author: Luis Colorado <luis.colorado@spindrive.fi>
# Date: Thu Dec 12 09:12:05 EET 2024

OS           != uname -o
build_date   != LANG=C date 
doc_date     != LANG=C date +'%b %Y'

SED          ?= sed
SED_FLAGS    != ./mksedparms.sh < ./config.mk

include ./config.mk

.SUFFIXES: .1.gz .1 .1.in .c.in .h.in .mo .po .po.in .pot 

.h.in.h .c.in.c .1.in.1 .po.in.po:
	sed -E $(SED_FLAGS) < $< > $@

.po.mo:
	msgfmt -o $@ $<

.1.1.gz:
	gzip < $< > $@

toclean += config.h.in config.h
