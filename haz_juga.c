/* $Id: haz_juga.c,v 1.9 2001/12/25 05:03:44 luis Exp $
 * haz_jugada.c -- rutina para efectuar una jugada.
 * Autor: Luis Colorado.
 * Version: 1.00 (30.1.93)
 */

#include <malloc.h>
#include "defs.h"

static char RCS_Id[] = "\n$Id: haz_juga.c,v 1.9 2001/12/25 05:03:44 luis Exp $\n";

struct posicion {
	int x;
	int y;
	struct posicion *ant;
	struct posicion *sig;
};

void revela_tablero()
{
	int x, y;
	for (y = 0; y < filas; y++) {
		for (x = 0; x < columnas; x++) {
			move(y+2, 2*x + 3);
			if ((tablero[y][x] & MINA) &&
				!(tablero[y][x] & MARCADO)) {
				addstr("#");
			} else if (!(tablero[y][x] & MINA) &&
				(tablero [y][x] & MARCADO)) {
				addstr("?");
			}
		}
	}
} /* revela_tablero */

void haz_jugada ()
{
	struct posicion *lista_posiciones, *p;

	if (!(tablero [pos_y][pos_x] & CUBIERTO) ||
		(tablero [pos_y][pos_x] & MARCADO)) {
		beep ();
		return;
	}
	lista_posiciones = malloc (sizeof (struct posicion));
	lista_posiciones->x = pos_x;
	lista_posiciones->y = pos_y;
	lista_posiciones->sig = NULL;
	lista_posiciones->ant = NULL;
	while (lista_posiciones) {
		/* sacamos el valor de la lista */
		p = lista_posiciones;
		lista_posiciones = lista_posiciones->sig;
		if (tablero [p->y][p->x] & CUBIERTO) {
			/* DESCUBRIMOS */
			tablero [p->y][p->x] &= ~CUBIERTO;
			quedan--;
			move (1, 3);
			printw ("%d-", quedan);
			move (p->y + 2, 2 * p->x + 3);
			if (tablero [p->y][p->x] & MINA) {
				revela_tablero();
				beep ();
				mvaddstr(pos_y+2, 2*pos_x+2, "[*]");
				refresh ();
				sleep(3);
				endwin ();
				printf ("HA TOCADO UNA MINA!!!\n");
				exit (0);
			}
			if ((tablero [p->y][p->x] & MASCARA) == 0) {
				addstr (" ");
			} else {
				printw ("%d",
					tablero [p->y][p->x]
					& MASCARA);
			}
		} /* if (tablero [p->y][p->x] & CUBIERTO) */
		if (!quedan) {
			revela_tablero();
			beep ();
			refresh ();
			endwin ();
			printf ("HAS GANADO ESTA VEZ, PRUEBA OTRA SI TE ATREVES.\n");
			exit (0);
		} /* if */
		/* si el valor es 0 exploramos */
		if ((tablero [p->y][p->x] & MASCARA) == 0) {
			struct posicion *q;
			if (p->y > 0) {
				if (p->x > 0) {
					if ((tablero [p->y - 1][p->x - 1] & CUBIERTO)
						&& !(tablero[p->y - 1][p->x - 1] & MARCADO))
					{
						q = malloc (sizeof (struct posicion));
						q->x = p->x - 1;
						q->y = p->y - 1;
						q->sig = lista_posiciones;
						lista_posiciones = q;
					} /* if */
				} /* if */
				if ((tablero [p->y - 1][p->x] & CUBIERTO)
					&& !(tablero [p->y - 1][p->x] & MARCADO))
				{
					q = malloc (sizeof (struct posicion));
					q->x = p->x;
					q->y = p->y - 1;
					q->sig = lista_posiciones;
					lista_posiciones = q;
				} /* if */
				if (p->x < columnas - 1) {
					if ((tablero [p->y - 1][p->x + 1] & CUBIERTO)
						&& !(tablero [p->y - 1][p->x + 1] & MARCADO))
					{
						q = malloc (sizeof (struct posicion));
						q->x = p->x + 1;
						q->y = p->y - 1;
						q->sig = lista_posiciones;
						lista_posiciones = q;
					} /* if */
				} /* if */
			} /* if */
			if (p->x > 0) {
				if ((tablero [p->y][p->x - 1] & CUBIERTO)
					&& !(tablero [p->y][p->x - 1] & MARCADO))
				{
					q = malloc (sizeof (struct posicion));
					q->x = p->x - 1;
					q->y = p->y;
					q->sig = lista_posiciones;
					lista_posiciones = q;
				} /* if */
			} /* if */
			if (p->x < columnas - 1) {
				if ((tablero [p->y][p->x + 1] & CUBIERTO)
					&& !(tablero [p->y][p->x + 1] & MARCADO))
				{
					q = malloc (sizeof (struct posicion));
					q->x = p->x + 1;
					q->y = p->y;
					q->sig = lista_posiciones;
					lista_posiciones = q;
				} /* if */
			} /* if */
			if (p->y < filas - 1) {
				if (p->x > 0) {
					if ((tablero [p->y + 1][p->x - 1] & CUBIERTO)
						&& !(tablero [p->y + 1][p->x - 1] & MARCADO))
					{
						q = malloc (sizeof (struct posicion));
						q->x = p->x - 1;
						q->y = p->y + 1;
						q->sig = lista_posiciones;
						lista_posiciones = q;
					}
				} /* if */
				if ((tablero [p->y + 1][p->x] & CUBIERTO)
					&& !(tablero [p->y + 1][p->x] & MARCADO))
				{
					q = malloc (sizeof (struct posicion));
					q->x = p->x;
					q->y = p->y + 1;
					q->sig = lista_posiciones;
					lista_posiciones = q;
				} /* if */
				if (p->x < columnas - 1) {
					if ((tablero [p->y + 1][p->x + 1] & CUBIERTO)
						&& !(tablero [p->y + 1][p->x + 1] & MARCADO))
					{
						q = malloc (sizeof (struct posicion));
						q->x = p->x + 1;
						q->y = p->y + 1;
						q->sig = lista_posiciones;
						lista_posiciones = q;
					} /* if */
				} /* if */
			} /* if */
		} /* if ((tablero [p->y][p->x] & MASCARA) == 0) */
		free (p);
	} /* while (lista_posiciones) */
} /* haz_jugada */

void marca_casilla()
{
	if (!(tablero [pos_y][pos_x] & CUBIERTO)) {
		beep ();
		return;
	}
	tablero [pos_y][pos_x] ^= MARCADO;
	mvaddstr (pos_y + 2, 2 * pos_x + 3,
		(tablero[pos_y][pos_x] & MARCADO) ? "@" : ".");

} /* marca_posicion */

/* $Id: haz_juga.c,v 1.9 2001/12/25 05:03:44 luis Exp $ */
