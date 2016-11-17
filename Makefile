# $Id: Makefile,v 1.7 2014/04/10 14:14:20 luis Exp $
# Date: Fri Nov 18 20:23:14 CET 2011
# Author: Luis Colorado <lc@luiscoloradosistemas.com>
# Disclaimer: (C) 1993--2014 LUIS COLORADO SISTEMAS S.L.U.
#		All rights reserved.
# 

package = buscamin
version = 1.2

prefix = $(HOME)
bindir = $(prefix)/bin
localedir = $(prefix)/share/locale

langs = es_ES.ASCII es_ES.ISO-8859-1 es_ES.UTF-8 es_ES
targets = $(package) $(langs:=.mo)

INSTALL = install -o `id -u` -g `id -u`
RM = rm -f

.PHONY: all clean install
.SUFFIXES: .c .o .pot .po .mo

all: $(targets)
clean:
	$(RM) buscamin $($(package)_objs) $(langs:=.mo)
install: $(targets)
	-@for i in $(langs); do \
		echo $(INSTALL) -m 0755 -d $(localedir)/$$i/LC_MESSAGES; \
		$(INSTALL) -m 0755 -d $(localedir)/$$i/LC_MESSAGES; \
	done
	-$(INSTALL) -m 0711 buscamin $(bindir)/buscamin
	-@for i in $(langs) ; \
	do \
		echo $(INSTALL) -m 0644 $$i.mo \
		$(localedir)/$$i/LC_MESSAGES/$(package).mo; \
		$(INSTALL) -m 0644 $$i.mo \
		$(localedir)/$$i/LC_MESSAGES/$(package).mo; \
	done
deinstall:
	-$(RM) $(bindir)/buscamin
	-@for i in $(langs) ; \
	do \
		echo $(RM) $(localedir)/$$i/LC_MESSAGES/$(package).mo; \
		$(RM) $(localedir)/$$i/LC_MESSAGES/$(package).mo; \
	done

CFLAGS=-I/usr/local/include -I/usr/include/ncurses -g -DPACKAGE=\""$(package)"\" \
	   -DVERSION=\""$(version)"\" -DLOCALEDIR=\""$(localedir)"\"
LDFLAGS=-L/usr/local/lib

$(package)_objs=main.o iniciali.o tablero.o
$(package)_libs= -lintl -lncursesw
$(package): $($(package)_objs)
	$(CC) $(LDFLAGS) -o $(package) $($(package)_objs) $($(package)_libs)

$($(package)_objs): tablero.h
main.o iniciali.o: iniciali.h

.po.mo:
	msgfmt -o $@ $<

$(langs:=.po): $(package).pot
	msgmerge -U $@ $<

# $Id: Makefile,v 1.7 2014/04/10 14:14:20 luis Exp $
