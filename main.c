/* $Id: main.c,v 1.17 2014/04/10 14:18:22 luis Exp $
 * main.c -- programa principal del juego del buscaminas.
 * Autor: Luis Colorado <lc@luiscoloradosistemas.com>
 * Version: 1.00 (30.1.93)
 * Disclaimer: (C) 1993-2014 LUIS COLORADO SISTEMAS S.L.U.
 * 				All rights reserved.
 */

#include <stdlib.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <libintl.h>
#include <locale.h>

#include "tablero.h"
#include "iniciali.h"

#define D(S) __FILE__":%d: %s: " S, __LINE__, __func__
#define DEB(ST) do { ST; fprintf(stderr, D("%s\n"), #ST); } while (0)

#ifndef PACKAGE
#error PACKAGE must be defined for this to be compilable.
#endif
#ifndef LOCALEDIR
#error LOCALEDIR must be defined for this to be compilable.
#endif

static char RCS_Id[] =
"\n$Id: main.c,v 1.17 2014/04/10 14:18:22 luis Exp $\n";

int main (int argc, char **argv)
{
	int c;
	int n = 0; /* numero de posiciones a mover */
	struct tablero *t;
    char *s;

    setlocale(LC_ALL, "");
    bindtextdomain(PACKAGE, LOCALEDIR);
    s = textdomain(PACKAGE);

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
			message(t, "N = %d", n);
			break;

		case KEY_ESC: case KEY_BREAK: n = 0;
			message(t, "");
			break;

		case 'Q': case 'q':
			message(t, gettext("Exiting by user request"));
			NUMBER(t);
			refresh();
			endwin ();
			exit(2);

		case KEY_UP: case 'k':
			t->y -= n ? n : 1; n = 0;
			if (t->y < 0) t->y = 0;
			message(t, "");
			break;

		case 'K': n = 0;
			t->y = 0;
			message(t, "");
			break;

		case KEY_DOWN: case 'j':
			t->y += n ? n : 1; n = 0;
			if (t->y >= t->lin) t->y = t->lin - 1;
			message(t, "");
			break;

		case 'J': n = 0;
			t->y = t->lin-1;
			message(t, "");
			break;

		case KEY_LEFT: case 'h':
			t->x -= n ? n : 1; n = 0;
			if (t->x <= 0) t->x = 0;
			message(t, "");
			break;

		case 'H': n = 0;
			t->x = 0;
			message(t, "");
			break;

		case KEY_RIGHT: case 'l':
			t->x += n ? n : 1; n = 0;
			if (t->x >= t->col) t->x = t->col-1;
			message(t, "");
			break;

		case 'L': n = 0;
			t->x = t->col-1;
			message(t, "");
			break;

		case KEY_CTRL_L:
			clear(); 
			drawTablero(t);
			break;

		case 'x': case 'X':
			n = 0;
			if (isCovered(t, t->x, t->y)) {
				switchMarked(t, t->x, t->y);
				message(t,
                    isMarked(t, t->x, t->y)
                        ? gettext("Mark set at position (%d, %d)")
                        : gettext("Mark clear at position (%d, %d)"),
					t->x, t->y);
				break;
			} /* if */
			/* NO BREAK HERE */
		case KEY_ENTER: case KEY_ESP:
		case 'c': case 'C':
			n = 0;
			if (	!isCovered(t, t->x, t->y)
				&& !isMarked(t, t->x, t->y)
				&& (numMines(t, t->x, t->y) == numMarks(t, t->x, t->y))
			) {
				/* jugamos las ocho casillas adyacentes */
				doJugada(t, t->x-1, t->y-1);
				doJugada(t, t->x-1, t->y  );
				doJugada(t, t->x-1, t->y+1);
				doJugada(t, t->x  , t->y-1);
				doJugada(t, t->x  , t->y+1);
				doJugada(t, t->x+1, t->y-1);
				doJugada(t, t->x+1, t->y  );
				doJugada(t, t->x+1, t->y+1);
				message(t, gettext("Playing eight neighbour places"));
			} else
				doJugada(t, t->x, t->y);
			if (!t->quedan) {
				NUMBER(t);
				message(t, gettext("YOU WIN!!!"));
				beep();
				refresh();
				sleep(3);
				endwin();
				exit(0);
			} /* if */
			if (t->quedan < 10)
				message(t, gettext("%d mines left"), t->quedan);
			break;

		default: n = 0;
			beep ();
			message(t, gettext("Incorrect key hit!"));
			break;

		} /* switch */
	} /* for(;;) */
} /* main */

/* $Id: main.c,v 1.17 2014/04/10 14:18:22 luis Exp $ */
