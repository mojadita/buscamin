# $Id: Makefile,v 1.4 2011/11/18 19:27:13 luis Exp $
# Date: Fri Nov 18 20:23:14 CET 2011
# Author: Luis Colorado <lc@luiscoloradosistemas.com>
# 

.PHONY: all clean

all: buscamin
clean:
	$(RM) buscamin $(BUSCAMIN_OBJS)

CFLAGS=-I/usr/include/ncurses

BUSCAMIN_OBJS=coloca_c.o error.o haz_juga.o iniciali.o main.o pinta_ta.o vars.o
buscamin: $(BUSCAMIN_OBJS)
	$(CC) -o buscamin $(BUSCAMIN_OBJS) -lncurses

$(BUSCAMIN_OBJS): defs.h

# $Id: Makefile,v 1.4 2011/11/18 19:27:13 luis Exp $
