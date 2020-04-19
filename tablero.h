/* $Id: tablero.h,v 1.4 2014/04/10 14:18:22 luis Exp $
 * Author: Luis Colorado <lc@luiscoloradosistemas.com>
 * Date: mar abr  8 09:44:19 CEST 2014
 * Disclaimer: (C) 1993-2020 LUIS COLORADO SISTEMAS S.L.U.
 * 			All rights reserved.
 * License: BSD
 */

#ifndef _TABLERO_H
#define _TABLERO_H

#include <stdarg.h>
#include <curses.h>
#include <stdlib.h>

#include <libintl.h>
#if 0
#define _(X) gettext (X)
#define gettext_noop(X) X
#define N_(X) gettext_noop(X)
#endif

static char RCS_Id_tablero_h[] =
"\n$Id: tablero.h,v 1.4 2014/04/10 14:18:22 luis Exp $\n"; 

#ifndef NULL
#define NULL 0
#endif

#ifdef ACS_ULCORNER /* si ncurses.h */
#define HLINE()		do {addch(ACS_HLINE); addch(ACS_HLINE); } while(0)
#define VLINE()		do {addch(ACS_VLINE); } while(0);
#define ULCORNER()	do {addch(ACS_ULCORNER); addch(ACS_HLINE); }while(0)
#define URCORNER()	do {addch(ACS_URCORNER); }while(0)
#define LLCORNER()	do {addch(ACS_LLCORNER); addch(ACS_HLINE); }while(0)
#define LRCORNER()	do {addch(ACS_LRCORNER); }while(0)
#define NUMBER(t)		do {mvprintw (1,3,"<%d,%d>", t->num_minas, t->quedan); addch(ACS_HLINE); }while(0)
#else /* curses.h normal */
#define HLINE()		do {addstr ("--"); }while(0)
#define VLINE()		do {addch('|'); }while(0)
#define ULCORNER()	do {addstr ("+-"); }while(0)
#define URCORNER()	do {addstr ("+"); }while(0)
#define LLCORNER()	do {addstr ("+-"); }while(0)
#define LRCORNER()	do {addstr ("+"); }while(0)
#define NUMBER(t)		do {mvprintw (1,3,"<%d,%d>-", t->num_minas, t->quedan); }while(0)
#endif

#define KEY_ESC		'\033'
#define KEY_ESP		' '
#define CONTROL(X)	((X) ^ '@')
#define KEY_CTRL_L	CONTROL('L')

#define PROBAB			12	/* la probabilidad por defecto de mina */

#define randomize() srand (time (0))
#define random(N) (rand () % (N))

#define MASCARA		0x0f
#define ISMINE		0x10
#define ISCOVERED	0x20
#define ISMARKED	0x40

struct tablero {
	int lin, col;
	int x, y;
	int pos_x, pos_y;
	char **tablero;
	int num_minas;
	int quedan;
}; /* struct tablero */

struct tablero *new_tablero (int dim_x, int dim_y, int prob);
int isCovered(struct tablero *t, int x, int y);
int isMarked(struct tablero *t, int x, int y);
void switchMarked(struct tablero *t, int x, int y);
int isMine(struct tablero *t, int x, int y);
int numMines(struct tablero *t, int x, int y);
int numMarks(struct tablero *t, int x, int y);
void Mark(struct tablero *t, int x, int y);
void unMark(struct tablero *t, int x, int y);
void drawCell(struct tablero *t, int x, int y);
void drawTablero(struct tablero *t);
void setCursor(struct tablero *t);
void doJugada(struct tablero *t, int x, int y);
int message(struct tablero *t, char *fmt, ...);
int messagev(struct tablero *t, char *fmt, va_list l);

#endif /* _TABLERO_H */
/* $Id: tablero.h,v 1.4 2014/04/10 14:18:22 luis Exp $ */
