/* $Id: defs.h,v 1.9 2011/11/18 19:27:13 luis Exp $
 * defs.h -- fichero con definiciones para el juego del buscaminas.
 * Autor: Luis Colorado.
 * Version: 1.00 (30.1.93)
 */

#ifndef _defs_h
#define _defs_h
#include <curses.h>
#include <stdio.h>
#include <stdlib.h>

#ifndef NULL
#define NULL 0
#endif

#ifdef ACS_ULCORNER /* si ncurses.h */
#define HLINE()		addch(ACS_HLINE); addch(ACS_HLINE);
#define VLINE()		addch(ACS_VLINE);
#define ULCORNER()	addch(ACS_ULCORNER); addch(ACS_HLINE);
#define URCORNER()	addch(ACS_URCORNER);
#define LLCORNER()	addch(ACS_LLCORNER); addch(ACS_HLINE);
#define LRCORNER()	addch(ACS_LRCORNER);
#define NUMBER()	mvprintw (1,3,"<%d,%d>", num_minas, quedan); addch(ACS_HLINE);
#else /* curses.h normal */
#define HLINE()		addstr ("--");
#define VLINE()		addch('|');
#define ULCORNER()	addstr ("+-");
#define URCORNER()	addstr ("+");
#define LLCORNER()	addstr ("+-");
#define LRCORNER()	addstr ("+");
#define NUMBER()	mvprintw (1,3,"<%d,%d>-", num_minas, quedan);
#endif

static char RCS_Id_defs_h[] = "\n$Id: defs.h,v 1.9 2011/11/18 19:27:13 luis Exp $\n";

extern int filas;
extern int columnas;
extern int pos_x;
extern int pos_y;
extern char **tablero;
extern int num_minas;
extern int quedan;

extern int x_salv, y_salv;

/* prototipos de funciones */
void inicializa_tablero ();
void coloca_cursor ();
void pinta_tablero ();
void haz_jugada ();

#define KEY_ESC		'\033'
#define KEY_ESP		' '

#define CUBIERTO	0x80
#define MINA		0x40
#define MARCADO		0x20
#define MASCARA		0x0f

#define PROBAB		12	/* la probabilidad de mina */

#define randomize() srand (time (0))
#define random(N) (rand () % (N))

#endif
/* $Id: defs.h,v 1.9 2011/11/18 19:27:13 luis Exp $ */
