/* $Id: main.c,v 1.7 2002/01/18 11:55:12 luis Exp $
 * main.c -- programa principal del juego del buscaminas.
 * Autor: Luis Colorado
 * Version: 1.00 (30.1.93)
 */

#include "defs.h"

static char RCS_Id[] = "\n$Id: main.c,v 1.7 2002/01/18 11:55:12 luis Exp $\n";

int main (argc, argv)
int argc;
char *argv [];
{
	int c;

	inicializa_tablero (argc, argv);
	initscr ();
	raw();
	noecho();
	cbreak();
	keypad (stdscr, 1);
	pinta_tablero ();
	for (;;) {
		NUMBER();
		coloca_cursor ();
		c = getch ();
		switch (c) {
		case KEY_ESC: case KEY_BREAK:
		case 'Q': case 'q':
			endwin ();
			exit (0);
		case KEY_UP: case 'k':
			if (pos_y == 0) break;
			pos_y--; break;
		case 'K':
			pos_y = 0; break;
		case KEY_DOWN: case 'j':
			if (pos_y == filas - 1) break;
			pos_y++; break;
		case 'J':
			pos_y = filas - 1;
			break;
		case KEY_LEFT: case 'h':
			if (pos_x == 0) break;
			pos_x--; break;
		case 'H':
			pos_x = 0; break;
		case KEY_RIGHT: case 'l':
			if (pos_x == columnas - 1) break;
			pos_x++; break;
		case 'L':
			pos_x = columnas - 1; break;
		case KEY_ENTER: case KEY_ESP: case 'c':
			haz_jugada (); break;
		case 'x': case 'X':
			marca_casilla (); break;
		default:
			beep ();
		} /* switch */
	} /* for(;;) */
} /* main */

/* $Id: main.c,v 1.7 2002/01/18 11:55:12 luis Exp $ */
