/* $Id: pinta_ta.c,v 1.3 2001/12/24 01:24:51 luis Exp $
 * pinta_tablero.c -- rutina para pintar el tablero.
 * Autor: Luis Colorado.
 * Version: 1.00 (30.1.93)
 */

#include "defs.h"

static char RCS_Id[] = "\n$Id: pinta_ta.c,v 1.3 2001/12/24 01:24:51 luis Exp $\n";

void pinta_tablero ()
{
	int ancho, alto, i, j;

	ancho = 2 * columnas + 3;
	alto = filas + 2;

	clear ();
	mvaddstr (1, 1, "+-");
	for (i = 0; i < columnas; i++) {
		addstr ("--");
	}
	addstr ("+");
	for (i = 0; i < filas; i++) {
		mvaddstr (i + 2, 1, "| ");
		for (j = 0; j < columnas; j++)
			addstr (". ");
		addstr ("|");
	}
	mvaddstr (filas + 2, 1, "+-");
	for (i = 0; i < columnas; i++) {
		addstr ("--");
	}
	addstr ("+");
	move (1,3);
	printw ("%d-", quedan);
}

/* $Id: pinta_ta.c,v 1.3 2001/12/24 01:24:51 luis Exp $ */
