BUSCAMIN_OBJS=coloca_c.o error.o haz_juga.o iniciali.o main.o pinta_ta.o vars.o
buscamin: $(BUSCAMIN_OBJS)
	cc -o buscamin $(BUSCAMIN_OBJS) -lcurses
$(BUSCAMIN_OBJS): defs.h
