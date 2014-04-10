# $Id: Makefile,v 1.7 2014/04/10 14:14:20 luis Exp $
# Date: Fri Nov 18 20:23:14 CET 2011
# Author: Luis Colorado <lc@luiscoloradosistemas.com>
# Disclaimer: (C) 1993--2014 LUIS COLORADO SISTEMAS S.L.U.
#		All rights reserved.
# 

RM=rm -f

.PHONY: all clean

all: buscamin
clean:
	$(RM) buscamin $(BUSCAMIN_OBJS)

CFLAGS=-I/usr/include/ncurses -g

BUSCAMIN_OBJS=main.o iniciali.o tablero.o
buscamin: $(BUSCAMIN_OBJS)
	$(CC) -o buscamin $(BUSCAMIN_OBJS) -lncurses

$(BUSCAMIN_OBJS): tablero.h
main.o iniciali.o: iniciali.h

# $Id: Makefile,v 1.7 2014/04/10 14:14:20 luis Exp $
