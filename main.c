/* $Id: main.c,v 1.10 2002/02/06 13:39:40 luis Exp $
 * main.c -- programa principal del juego del buscaminas.
 * Autor: Luis Colorado
 * Version: 1.00 (30.1.93)
 */

#include "defs.h"

static char RCS_Id[] = "\n$Id: main.c,v 1.10 2002/02/06 13:39:40 luis Exp $\n";

int main (argc, argv)
int argc;
char *argv [];
{
	int c;
	int n = 0; /* numero de posiciones a mover */

	initscr ();
	inicializa_tablero (argc, argv);
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
		case '0': case '1': case '2': case '3': case '4':
		case '5': case '6': case '7': case '8': case '9':
			n *= 10; n += c - '0';
			break;
		case KEY_ESC: case KEY_BREAK:
		case 'Q': case 'q':
			endwin ();
			exit (0);
		case KEY_UP: case 'k':
			pos_y -= n ? n : 1; n = 0;
			if (pos_y < 0) pos_y = 0;
			break;
		case 'K': n = 0;
			pos_y = 0; break;
		case KEY_DOWN: case 'j':
			pos_y += n ? n : 1; n = 0;
			if (pos_y >= filas) pos_y = filas - 1;
			break;
		case 'J': n = 0;
			pos_y = filas - 1;
			break;
		case KEY_LEFT: case 'h':
			pos_x -= n ? n : 1; n = 0;
			if (pos_x <= 0) pos_x = 0;
			break;
		case 'H': n = 0;
			pos_x = 0; break;
		case KEY_RIGHT: case 'l':
			pos_x += n ? n : 1; n = 0;
			if (pos_x >= columnas) pos_x = columnas - 1;
			break;
		case 'L': n = 0;
			pos_x = columnas - 1; break;
		case KEY_ENTER: case KEY_ESP: case 'c': n = 0;
			haz_jugada (); break;
		case 'x': case 'X': n = 0;
			marca_casilla (); break;
		default: n = 0;
			beep ();
		} /* switch */
	} /* for(;;) */
} /* main */

/* $Id: main.c,v 1.10 2002/02/06 13:39:40 luis Exp $ */
