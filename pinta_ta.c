/* $Id: pinta_ta.c,v 1.5 2002/01/18 14:08:50 luis Exp $
 * pinta_tablero.c -- rutina para pintar el tablero.
 * Autor: Luis Colorado.
 * Version: 1.00 (30.1.93)
 */

#include "defs.h"

static char RCS_Id[] = "\n$Id: pinta_ta.c,v 1.5 2002/01/18 14:08:50 luis Exp $\n";

void pinta_tablero ()
{
	int ancho, alto, i, j;

	ancho = 2 * columnas + 3;
	alto = filas + 2;

	clear ();
	mvaddstr(0,0, "BUSCAMIN: (C) 1.995-2.002 Luis Colorado <luis.colorado@hispalinux.es>");
	move(1,1);
	ULCORNER();
	for (i = 0; i < columnas; i++) {
		HLINE();
	}
	URCORNER();
	for (i = 0; i < filas; i++) {
		move(i+2,1);
		VLINE();
		addch(' ');
		for (j = 0; j < columnas; j++)
			addstr (". ");
		VLINE();
	}
	move(filas+2,1);
	LLCORNER();
	for (i = 0; i < columnas; i++) {
		HLINE();
	}
	LRCORNER();
} /* pinta_tablero */

/* $Id: pinta_ta.c,v 1.5 2002/01/18 14:08:50 luis Exp $ */
