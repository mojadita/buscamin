/* $Id: tablero.c,v 1.1 2014/04/09 13:59:41 luis Exp $
 * Author: Luis Colorado <lc@luiscoloradosistemas.com>
 * Date: mar abr  8 09:50:38 CEST 2014
 * Disclaimer: (C) 2014 LUIS COLORADO SISTEMAS S.L.U.
 * 			All rights reserved.
 */

#include <stdlib.h>
#include <stdio.h>
#include <curses.h>
#include <assert.h>
#include "tablero.h"

struct tablero *new_tablero(int dim_x, int dim_y, int prob)
{
	struct tablero *res;
	int x, y;

	assert(res = malloc(sizeof(struct tablero)));
	res->lin = dim_y;
	res->col = dim_x;
	res->x = res->y = 0;

	assert(res->tablero = calloc(res->lin, sizeof (char *)));

	for (y = 0; y < res->lin; y++) {
		assert(res->tablero[y] = malloc(res->col));
		for (x = 0; x < res->col; x++) {
			if (random(100) < prob) {
				res->tablero[y][x] = ISMINE | ISCOVERED;
				res->num_minas++;
			} else {
				res->tablero[y][x] = ISCOVERED;
			} /* if */
		} /* for j */
	} /* for i */

	/* inicializamos el número de minas alrededor de la casilla */
	for (y = 0; y < res->lin; y++) {
		for (x = 0; x < res->col; x++) {
			if (isMine(res, x-1, y-1)) res->tablero[y][x]++;
			if (isMine(res, x  , y-1)) res->tablero[y][x]++;
			if (isMine(res, x+1, y-1)) res->tablero[y][x]++;
			if (isMine(res, x-1, y  )) res->tablero[y][x]++;
			if (isMine(res, x+1, y  )) res->tablero[y][x]++;
			if (isMine(res, x-1, y+1)) res->tablero[y][x]++;
			if (isMine(res, x  , y+1)) res->tablero[y][x]++;
			if (isMine(res, x+1, y+1)) res->tablero[y][x]++;
		} /* for j */
	} /* for i */
	res->quedan = res->lin * res->col - res->num_minas;
	return res;
} /* new_tablero */

int isCovered(struct tablero *t, int x, int y)
{
	if ((x < 0) || (y < 0) || (x >= t->col) || (y >= t->lin))
		return TRUE;
	else return t->tablero[y][x] & ISCOVERED;
} /* isCovered */

int isMarked(struct tablero *t, int x, int y)
{
	if ((x < 0) || (y < 0) || (x >= t->col) || (y >= t->lin))
		return FALSE;
	else return t->tablero[y][x] & ISMARKED;
} /* isMarked */

int isMine(struct tablero *t, int x, int y)
{
	if ((x < 0) || (y < 0) || (x >= t->col) || (y >= t->lin))
		return FALSE;
	else return t->tablero[y][x] & ISMINE;
} /* isMine */

int numMines(struct tablero *t, int x, int y)
{
	if ((x < 0) || (y < 0) || (x >= t->col) || (y >= t->lin))
		return 0;
	else return t->tablero[y][x] & MASCARA;
} /* numMines */

int numMarks(struct tablero *t, int x, int y)
{
	int res = 0;
	if (isMarked(t, x-1, y-1)) res++;
	if (isMarked(t, x  , y-1)) res++;
	if (isMarked(t, x+1, y-1)) res++;
	if (isMarked(t, x-1, y  )) res++;
	if (isMarked(t, x+1, y  )) res++;
	if (isMarked(t, x-1, y+1)) res++;
	if (isMarked(t, x  , y+1)) res++;
	if (isMarked(t, x+1, y+1)) res++;
	return res;
} /* numMarks */

void switchMarked(struct tablero *t, int x, int y)
{
	if (isCovered(t, x, y)) {
		t->tablero[y][x] ^= ISMARKED;
		move(y + 2, 2*x + 2);
		if (isMarked(t, x, y)) addstr("@");
		else addstr(".");
	} else {
		beep();
	}
} /* switchMarked */

void uncover(struct tablero *t, int x, int y)
{
	t->tablero[y][x] &= ~ISCOVERED;
	drawCell(t, x, y);
} /* uncover */

void drawCell(struct tablero *t, int x, int y)
{
	move(2 + y, 2 + 2*x);
	if (isCovered(t, x, y)) {
		if (isMarked(t, x, y))
			addstr("@");
		else
			addstr(".");
	} else { /* !isCovered */
		switch(t->tablero[y][x] & (ISMARKED | ISMINE)) {
		case 0: /* nor marked nor mine nor covered */
			switch(numMines(t, x, y)) {
			case 0: addstr(" "); break;
			case 1: addstr("1"); break;
			case 2: addstr("2"); break;
			case 3: addstr("3"); break;
			case 4: addstr("4"); break;
			case 5: addstr("5"); break;
			case 6: addstr("6"); break;
			case 7: addstr("7"); break;
			} /* switch */
			break;
		case ISMARKED: /* MARKED, BUT NOT MINE */
			addstr("?"); break;
		case ISMINE: /* MINE, BUT NOT MARKED */
			addstr("#"); break;
		case ISMINE | ISMARKED:
			addstr("!"); break;
		} /* switch */
	} /* if */
} /* drawCell */

static void drawHLine(struct tablero *t)
{
	int i;
	for (i = 0; i < t->col; i++)
		HLINE();
} /* drawHLine */

static void drawFrame(struct tablero *t)
{
	int i;
	move(1, 0);
	ULCORNER();
	drawHLine(t);
	URCORNER();
	for (i = 0; i < t->lin; i++) {
		move(i + 2, 0); VLINE();
		move(i + 2, t->col*2 + 2); VLINE();
	} /* for */
	move(t->lin + 2, 0);
	LLCORNER();
	drawHLine(t);
	LRCORNER();
} /* drawFrame */

void drawTablero(struct tablero *t)
{
	int x, y;

	clear();
	mvaddstr(0,0,
			"BUSCAMIN: (C) 1.995-2.014 Luis Colorado "
			"<lc@luiscoloradosistemas.com>");
	drawFrame(t);
	for (y = 0; y < t->lin; y++)
		for (x = 0; x < t->col; x++)
			drawCell(t, x, y);
	setCursor(t);
} /* drawTablero */

void setCursor(struct tablero *t)
{
	move(t->y + 2, t->x*2 + 2);
}

void doJugada(struct tablero *t, int x, int y)
{
	int i, j;
	/* Si no est\'a marcado, no est\'a cubierto y el n\'umero de minas
	 * es igual que el n\'umero de marcas alrededor hay que jugar todas
	 * las casillas alrededor de la actual (salvo las marcadas). */
#if 0
	if (	!isMarked(t, x, y) /* no est\'a marcada */
		&& !isCovered(t, x, y) /* no est\'a cubierta */
		&&	numMines(t, x, y) /* hay minas alrededor */
		&& (numMines(t, x, y) == numMarks(t, x, y)) /* numero de minas igual a numero de marcas */
	) {
		/* debemos jugar las ocho casillas de alrededor */
		if (x > 0) {
			if (y > 0)			doJugada(t, x-1, y-1);
									doJugada(t, x-1, y  );
			if (y < t->lin-1)	doJugada(t, x-1, y+1);
		} /* if */
		if (y > 0)				doJugada(t, x  , y-1);
		if (y < t->lin-1)		doJugada(t, x  , y+1);
		if (x < t->col-1) {
			if (y > 0)			doJugada(t, x+1, y-1);
									doJugada(t, x+1, y  );
			if (y < t->lin-1)	doJugada(t, x+1, y+1);
		} /* if */
		return;
	} /* if */
#endif
	if ((x < 0) || (x >= t->col) || (y < 0) || (y >= t->lin)) return;
	if (isMarked(t, x, y)) {
		/* intentamos jugar una posici\'on marcada, inv\'alido. */
		beep();
		return;
	} /* if */
	/* !isMarked */
	if (!isCovered(t, x, y)) return;
	/* !isMarked && isCovered */
	uncover(t, x, y);
	if (isMine(t, x, y)) {
		{ /* block */
			int x, y;
			for (y = 0; y < t->lin; y++)
				for (x = 0; x < t->col; x++)
					uncover(t, x, y);
		} /* block */
		mvaddstr(y+2, 2*x+1, "[*]");
		mvaddstr(t->lin+3, 0, "HA PISADO UNA MINA!!!");
		beep();
		refresh();
		sleep(3);
		endwin();
		exit(1);
	} /* if */
	t->quedan--;
	/* !isMarked && !isMine */
	if (numMines(t, x, y) == 0) {
		if (x > 0) {
			if (y > 0)			doJugada(t, x-1, y-1);
									doJugada(t, x-1, y  );
			if (y < t->lin-1)	doJugada(t, x-1, y+1);
		} /* if */
		if (y > 0)				doJugada(t, x  , y-1);
		if (y < t->lin-1)		doJugada(t, x  , y+1);
		if (x < t->col-1) {
			if (y > 0)			doJugada(t, x+1, y-1);
									doJugada(t, x+1, y  );
			if (y < t->lin-1)	doJugada(t, x+1, y+1);
		} /* if */
	} /* if */
} /* doJugada */

/* $Id: tablero.c,v 1.1 2014/04/09 13:59:41 luis Exp $ */
