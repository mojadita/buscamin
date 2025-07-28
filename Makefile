# $Id: Makefile,v 1.7 2014/04/10 14:14:20 luis Exp $
# Date: Fri Nov 18 20:23:14 CET 2011
# Author: Luis Colorado <lc@luiscoloradosistemas.com>
# Disclaimer: (C) 1993--2014 LUIS COLORADO SISTEMAS S.L.U.
#		All rights reserved.
# 

# OPERATING SYSTEM SUPPORT

include config-lib.mk

OWN-FreeBSD         = root
OWN-GNU/Linux       = bin
GRP-FreeBSD         = wheel
GRP-GNU/Linux       = bin

OWN = $(OWN-$(OS))
GRP = $(GRP-$(OS))
FMOD = 0444
XMOD = 0555
DMOD = 0555

langs     = es_ES.ASCII es_ES.ISO-8859-1 es_ES.UTF-8 es_ES es_CO.UTF-8 ru_RU.UTF-8 fr_FR.UTF-8
targets   = $(PROGRAM_NAME) $(langs:=.mo)
toclean   = $(PROGRAM_NAME) $(langs:=.mo) $(langs:=.po)
toinstall =                                            \
		$(langs:@lng@$(localedir)/$(lng)/LC_MESSAGES/$(PROGRAM_NAME).mo@) \
		$(bindir)/$(PROGRAM_NAME)

INSTALL   = install
IFLAGS    = -o $(OWN) -g $(GRP)
RM        = rm -f

.PHONY: all clean install

all: $(targets)

clean:
	$(RM) $(toclean)

install: $(toinstall)

$(langs:@lng@$(localedir)/$(lng)/LC_MESSAGES/$(PROGRAM_NAME).mo@): $(@:H:H:T:=.mo) $(@:H)
	-$(INSTALL) $(IFLAGS) -m $(FMOD) $(@:H:H:T:=.mo) $@

$(langs:@l@$(localedir)/$l/LC_MESSAGES@) $(langs:@l@$(localedir)/$l@): $(@:H)
	-$(INSTALL) $(IFLAGS) -m $(DMOD) -d $@
	-touch $@

$(bindir)/$(PROGRAM_NAME): $(@:T)
	-$(INSTALL) $(IFLAGS) -m $(XMOD) $(@:T) $(@)

deinstall uninstall:
	-$(RM) $(toinstall)

CFLAGS-FreeBSD    = -I/usr/local/include -I/usr/include/ncurses
CFLAGS-GNU/Linux  =
LDFLAGS-FreeBSD   = -L/usr/local/lib
LDFLAGS-GNU/Linux =
LIBS-FreeBSD      = -lintl -lncursesw
LIBS-GNU/Linux    = -lncursesw

CFLAGS            = $(CFLAGS-$(OS))
LIBS              = $(LIBS-$(OS))
LDFLAGS           = $(LDFLAGS-$(OS))

$(PROGRAM_NAME)_objs=main.o iniciali.o tablero.o
toclean += $($(PROGRAM_NAME)_objs)

$(PROGRAM_NAME): $($(PROGRAM_NAME)_objs)
	$(CC) $(LDFLAGS) -o $@ $($@_objs) $(LIBS)

config.h.in: config.mk config.h.in.sh
	./config.h.in.sh < config.mk >config.h.in
toclean += config.h.in config.h

iniciali.o: iniciali.c  tablero.h
main.o: main.c  config.h tablero.h  iniciali.h
tablero.o: tablero.c  config.h  tablero.h
