/* tablero.c -- board implementation.
 * Author: Luis Colorado <luiscoloradourcola@gmail.com>
 * Date: mar abr  8 09:50:38 CEST 2014
 * Copyright: (C) 1993-2025 Luis Colorado.  All rights reserved.
 * License: BSD
 */

#include <stdlib.h>
#include <stdio.h>
#include <curses.h>
#include <assert.h>
#include <unistd.h>

#include "config.h"
#include "tablero.h"

struct tablero *
new_tablero(
        int dim_x,
        int dim_y,
        int prob)
{
    struct tablero *res = malloc(sizeof (*res));
    assert(res != NULL);

    res->lin       = dim_y;
    res->col       = dim_x;
    res->x         = 0;
    res->y         = 0;
    res->num_minas = 0;

    res->tablero = calloc(res->lin, sizeof *res->tablero);
    assert(res->tablero != NULL);

    for (int y = 0; y < res->lin; y++) {
        res->tablero[y] = calloc(res->col, sizeof *res->tablero[y]);
        assert(res->tablero[y] != NULL);
        for (int x = 0; x < res->col; x++) {
            if (random(100) < prob) {
                res->tablero[y][x] = ISMINE | ISCOVERED;
                res->num_minas++;
            } else {
                res->tablero[y][x] = ISCOVERED;
            } /* if */
        } /* for j */
    } /* for i */

    /* inicializamos el número de minas alrededor de la casilla */
    for (int y = 0; y < res->lin; y++) {
        for (int x = 0; x < res->col; x++) {
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

int
isCovered(
        struct tablero *t,
        int             x,
        int             y)
{
    if ((x < 0) || (y < 0) || (x >= t->col) || (y >= t->lin))
        return TRUE;
    return t->tablero[y][x] & ISCOVERED;
} /* isCovered */

int
isMarked(
        struct tablero *t,
        int             x,
        int             y)
{
    if ((x < 0) || (y < 0) || (x >= t->col) || (y >= t->lin))
        return FALSE;
    return t->tablero[y][x] & ISMARKED;
} /* isMarked */

int
isMine(
        struct tablero *t,
        int             x,
        int             y)
{
    if ((x < 0) || (y < 0) || (x >= t->col) || (y >= t->lin))
        return FALSE;
    return t->tablero[y][x] & ISMINE;
} /* isMine */

int
numMines(
        struct tablero *t,
        int             x,
        int             y)
{
    if ((x < 0) || (y < 0) || (x >= t->col) || (y >= t->lin))
        return 0;
    return t->tablero[y][x] & MASCARA;
} /* numMines */

int
numMarks(
        struct tablero *t,
        int             x,
        int             y)
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

void
switchMarked(
        struct tablero *t,
        int             x,
        int             y)
{
    if (isCovered(t, x, y)) {
        if (!isMarked(t, x, y) && (t->num_minas <= 0)) {
            beep();
            return;
        } /* if */
        t->tablero[y][x] ^= ISMARKED;
        drawCell(t, x, y);
        if (isMarked(t, x, y))
             t->num_minas--;
        else t->num_minas++;
    } /* if */
} /* switchMarked */

void
uncover(
        struct tablero *t,
        int             x,
        int             y)
{
    if (!isCovered(t, x, y)) return;
    t->tablero[y][x] ^= ISCOVERED;
    drawCell(t, x, y);
    if (!isMine(t, x, y)) t->quedan--;
} /* uncover */

void
drawCell(
        struct tablero *t,
        int             x,
        int             y)
{
    move(2 + y, 1 + 2*x);
    if (isCovered(t, x, y)) {
        if (isMarked(t, x, y))
            addstr(" @");
        else
            addstr(" .");
    } else { /* !isCovered */
        switch(t->tablero[y][x] & (ISMARKED | ISMINE)) {
        case 0: /* nor marked nor mine nor covered */
            switch(numMines(t, x, y)) {
            case 0: addstr("  "); break;
            case 1: addstr(" 1"); break;
            case 2: addstr(" 2"); break;
            case 3: addstr(" 3"); break;
            case 4: addstr(" 4"); break;
            case 5: addstr(" 5"); break;
            case 6: addstr(" 6"); break;
            case 7: addstr(" 7"); break;
            } /* switch */
            break;
        case ISMARKED: /* MARKED, BUT NOT MINE */
            addstr(" ?"); break;
        case ISMINE:   /* MINE, BUT NOT MARKED */
            addstr(" #"); break;
        case ISMINE | ISMARKED:
            addstr(" !"); break;
        } /* switch */
    } /* if */
} /* drawCell */

static void
drawHLine(
        struct tablero *t)
{
    int i;
    for (i = 0; i < t->col; i++)
        HLINE();
} /* drawHLine */

static void
drawFrame(
        struct tablero *t)
{
    move(1, 0);
    ULCORNER();
    drawHLine(t);
    URCORNER();
    for (int i = 0; i < t->lin; i++) {
        move(i + 2, 0); VLINE();
        move(i + 2, t->col*2 + 2); VLINE();
    } /* for */
    move(t->lin + 2, 0);
    LLCORNER();
    drawHLine(t);
    LRCORNER();
} /* drawFrame */

void
drawTablero(
        struct tablero *t)
{
    int x, y;

    clear();
    mvaddstr(0,0,
            PACKAGE " v-" VERSION ": (C) " COPYRIGHT_YEARS " "
            AUTHOR_NAME " <" AUTHOR_EMAIL ">");
    drawFrame(t);
    for (y = 0; y < t->lin; y++)
        for (x = 0; x < t->col; x++)
            drawCell(t, x, y);
    setCursor(t);
} /* drawTablero */

void
setCursor(
        struct tablero *t)
{
    move(t->y + 2, t->x*2 + 2);
}

void
doJugada(
        struct tablero *t,
        int             x,
        int             y)
{
    if ((x < 0) || (x >= t->col) || (y < 0) || (y >= t->lin) ||
        isMarked(t, x, y) || !isCovered(t, x, y)) return;
    /* !isMarked && isCovered */

    uncover(t, x, y);
    if (isMine(t, x, y)) {
        { /* block */
            int x, y;
            for (y = 0; y < t->lin; y++)
                for (x = 0; x < t->col; x++)
                    uncover(t, x, y);
        } /* block */
        mvaddstr(y + 2, 2*x + 1, "[*]");
        NUMBER(t);
        message(t, gettext("YOU HAVE STEP OVER A MINE!!!"));
        beep();
        refresh();
        sleep(3);
        endwin();
        exit(EXIT_FAILURE);
    } /* if */
    /* !isMarked && !isMine */
    if (numMines(t, x, y) == 0) {
        doJugada(t, x-1, y-1);
        doJugada(t, x-1, y  );
        doJugada(t, x-1, y+1);
        doJugada(t, x  , y-1);
        doJugada(t, x  , y+1);
        doJugada(t, x+1, y-1);
        doJugada(t, x+1, y  );
        doJugada(t, x+1, y+1);
    } /* if */
} /* doJugada */

int
messagev(
        struct tablero *t,
        char           *fmt,
        va_list         l)
{
    move(t->lin+3,0); clrtoeol();
    return vw_printw(stdscr, fmt, l);
} /* messagev */

int
message(
        struct tablero *t,
        char           *fmt,
                        ...)
{
    va_list l;
    int res;
    va_start(l, fmt);
    res = messagev(t, fmt, l);
    va_end(l);
    return res;
} /* message */
