/* $Id: main.c,v 1.4 2001/12/24 01:24:51 luis Exp $
 * main.c -- programa principal del juego del buscaminas.
 * Autor: Luis Colorado
 * Version: 1.00 (30.1.93)
 */

#include "defs.h"

static char RCS_Id[] = "\n$Id: main.c,v 1.4 2001/12/24 01:24:51 luis Exp $\n";

int main (argc, argv)
int argc;
char *argv [];
{
	int c;

	initscr ();
	raw();
	noecho();
	cbreak();
	keypad (stdscr, 1);
	inicializa_tablero (argc, argv);
	pinta_tablero ();
	for (;;) {
		coloca_cursor ();
		c = getch ();
		switch (c) {
		case KEY_ESC:
		case KEY_BREAK:
			endwin ();
			exit (0);
		case KEY_UP:
			if (pos_y == 0) break;
			pos_y--;
			break;
		case KEY_DOWN:
			if (pos_y == filas - 1) break;
			pos_y++;
			break;
		case KEY_LEFT:
			if (pos_x == 0) break;
			pos_x--;
			break;
		case KEY_RIGHT:
			if (pos_x == columnas - 1) break;
			pos_x++;
			break;
		case KEY_ENTER:
		case KEY_ESP:
			haz_jugada ();
			break;
		case 'x': case 'X':
			marca_casilla ();
			break;
		default:
			beep ();
		}
	}
}

/* $Id: main.c,v 1.4 2001/12/24 01:24:51 luis Exp $ */
