# $Id: Makefile,v 1.7 2014/04/10 14:14:20 luis Exp $
# Date: Fri Nov 18 20:23:14 CET 2011
# Author: Luis Colorado <lc@luiscoloradosistemas.com>
# Disclaimer: (C) 1993--2014 LUIS COLORADO SISTEMAS S.L.U.
#		All rights reserved.
# 

package = buscamin
version = 1.2

bindir = /usr/bin
localedir = /usr/share/locale

langs = es_ES.ASCII es_ES.ISO-8859-1 es_ES.UTF-8 es_ES
targets = $(package) $(langs:=.mo)

install = install

.PHONY: all clean install
.SUFFIXES: .c .o .pot .po .mo

all: $(targets)
clean:
	$(RM) buscamin $($(package)_objs) $(langs:=.mo)
install: $(targets)
	for i in $(langs); do \
		install -m 0555 -o root -g root -d $(localedir)/$$i/LC_MESSAGES; \
	done
	$(install) -m 0111 -o root -g root buscamin $(bindir)/buscamin
	for i in $(langs) ; do \
		$(install) -m 0444 -o root -g root $$i.mo \
		$(localedir)/$$i/LC_MESSAGES/$(package).mo; done

CFLAGS=-I/usr/include/ncurses -g -DPACKAGE=\""$(package)"\" \
	   -DVERSION=\""$(version)"\" -DLOCALEDIR=\""$(localedir)"\"

$(package)_objs=main.o iniciali.o tablero.o
$(package): $($(package)_objs)
	$(CC) -o $(package) $($(package)_objs) -lncursesw

$($(package)_objs): tablero.h
main.o iniciali.o: iniciali.h

%.mo: %.po
	msgfmt -o $@ $<

$(langs:=.po): $(package).pot
	msgmerge -U $@ $<

# $Id: Makefile,v 1.7 2014/04/10 14:14:20 luis Exp $
