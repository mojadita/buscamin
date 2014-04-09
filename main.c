/* $Id: main.c,v 1.12 2014/04/09 13:59:41 luis Exp $
 * main.c -- programa principal del juego del buscaminas.
 * Autor: Luis Colorado
 * Version: 1.00 (30.1.93)
 */

#include <stdlib.h>
#include <stdio.h>
#include "tablero.h"
#include "iniciali.h"

static char RCS_Id[] = "\n$Id: main.c,v 1.12 2014/04/09 13:59:41 luis Exp $\n";

int main (int argc, char **argv)
{
	int c;
	int n = 0; /* numero de posiciones a mover */
	struct tablero *t;

	initscr();
	t = inicializa_tablero (argc, argv);
	raw();
	noecho();
	cbreak();
	keypad (stdscr, 1);
	drawTablero(t);
	for (;;) {
		NUMBER(t);
		setCursor(t);
		refresh();
		c = getch();
		switch (c) {
		case '0': case '1': case '2': case '3': case '4':
		case '5': case '6': case '7': case '8': case '9':
			n *= 10; n += c - '0';
			break;
		case KEY_ESC: case KEY_BREAK:
			n = 0; break;
		case 'Q': case 'q':
			endwin ();
			exit(2);
		case KEY_UP: case 'k':
			t->y -= n ? n : 1; n = 0;
			if (t->y < 0) t->y = 0;
			break;
		case 'K': n = 0;
			t->y = 0; break;
		case KEY_DOWN: case 'j':
			t->y += n ? n : 1; n = 0;
			if (t->y >= t->lin) t->y = t->lin - 1;
			break;
		case 'J': n = 0;
			t->y = t->lin-1;
			break;
		case KEY_LEFT: case 'h':
			t->x -= n ? n : 1; n = 0;
			if (t->x <= 0) t->x = 0;
			break;
		case 'H': n = 0;
			t->x = 0; break;
		case KEY_RIGHT: case 'l':
			t->x += n ? n : 1; n = 0;
			if (t->x >= t->col) t->x = t->col-1;
			break;
		case 'L': n = 0;
			t->x = t->col-1; break;
		case KEY_ENTER: case KEY_ESP:
		case 'c': case 'C':
			n = 0;
			if (	!isCovered(t, t->x, t->y)
				&& !isMarked(t, t->x, t->y)
				&& (numMines(t, t->x, t->y) == numMarks(t, t->x, t->y))
			) {
					doJugada(t, t->x-1, t->y-1);
					doJugada(t, t->x-1, t->y  );
					doJugada(t, t->x-1, t->y+1);
					doJugada(t, t->x  , t->y-1);
					doJugada(t, t->x  , t->y+1);
					doJugada(t, t->x+1, t->y-1);
					doJugada(t, t->x+1, t->y  );
					doJugada(t, t->x+1, t->y+1);
			} /* if */
			doJugada(t, t->x, t->y);
			if (!t->quedan) {
				NUMBER(t);
				mvaddstr(t->lin+3, 0, "LAS SACASTE TODAS!!!");
				beep();
				refresh();
				sleep(3);
				endwin();
				exit(0);
			} /* if */
			break;
		case 'x': case 'X': n = 0;
			switchMarked(t, t->x, t->y);
			if (isMarked(t, t->x, t->y))
				t->num_minas--;
			else
				t->num_minas++;
			break;
		default: n = 0;
			beep ();
		} /* switch */
	} /* for(;;) */
} /* main */

/* $Id: main.c,v 1.12 2014/04/09 13:59:41 luis Exp $ */
