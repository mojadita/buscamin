/* $Id: vars.c,v 1.3 2001/12/24 01:24:51 luis Exp $
 * vars.c -- variables globales del juego del buscaminas.
 * Autor: Luis Colorado
 * Version: 1.00 (30.1.93)
 */

static char RCS_Id[] = "\n$Id: vars.c,v 1.3 2001/12/24 01:24:51 luis Exp $\n";

/* filas y columnas del tablero del juego del buscaminas */
int filas = 10;
int columnas = 10;
int pos_x = 0;
int pos_y = 0;
char **tablero;	/* tablero del juego */
int num_minas = 0;
int quedan;

int x_salv, y_salv;

/* $Id: vars.c,v 1.3 2001/12/24 01:24:51 luis Exp $ */
