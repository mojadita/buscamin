/* haz_jugada.c -- rutina para efectuar una jugada.
 * Autor: Luis Colorado.
 * Version: 1.00 (30.1.93)
 */

#include <malloc.h>
#include "defs.h"

#define NULL 0

struct posicion {
	int x;
	int y;
	struct posicion *ant;
	struct posicion *sig;
};

void haz_jugada ()
{
	struct posicion *lista_posiciones, *p;

	if (!(tablero [pos_y][pos_x] & CUBIERTO)) {
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
				beep ();
				addstr ("#");
				refresh ();
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
		}
		if (!quedan) {
			beep ();
			refresh ();
			endwin ();
			printf ("HAS GANADO ESTA VEZ, PRUEBA OTRA SI TE ATREVES.\n");
			exit (0);
		}
		/* si el valor es 0 exploramos */
		if ((tablero [p->y][p->x] & MASCARA) == 0) {
			struct posicion *q;
			if (p->y > 0) {
				if (p->x > 0) {
					if (tablero [p->y - 1][p->x - 1] & CUBIERTO)
					{
						q = malloc (sizeof (struct posicion));
						q->x = p->x - 1;
						q->y = p->y - 1;
						q->sig = lista_posiciones;
						lista_posiciones = q;
					}
				}
				if (tablero [p->y - 1][p->x] & CUBIERTO)
				{
					q = malloc (sizeof (struct posicion));
					q->x = p->x;
					q->y = p->y - 1;
					q->sig = lista_posiciones;
					lista_posiciones = q;
				}
				if (p->x < columnas - 1) {
					if (tablero [p->y - 1][p->x + 1] & CUBIERTO)
					{
						q = malloc (sizeof (struct posicion));
						q->x = p->x + 1;
						q->y = p->y - 1;
						q->sig = lista_posiciones;
						lista_posiciones = q;
					}
				}
			}
			if (p->x > 0) {
				if (tablero [p->y][p->x - 1] & CUBIERTO)
				{
					q = malloc (sizeof (struct posicion));
					q->x = p->x - 1;
					q->y = p->y;
					q->sig = lista_posiciones;
					lista_posiciones = q;
				}
			}
			if (p->x < columnas - 1) {
				if (tablero [p->y][p->x + 1] & CUBIERTO)
				{
					q = malloc (sizeof (struct posicion));
					q->x = p->x + 1;
					q->y = p->y;
					q->sig = lista_posiciones;
					lista_posiciones = q;
				}
			}
			if (p->y < filas - 1) {
				if (p->x > 0) {
					if (tablero [p->y + 1][p->x - 1] & CUBIERTO)
					{
						q = malloc (sizeof (struct posicion));
						q->x = p->x - 1;
						q->y = p->y + 1;
						q->sig = lista_posiciones;
						lista_posiciones = q;
					}
				}
				if (tablero [p->y + 1][p->x] & CUBIERTO)
				{
					q = malloc (sizeof (struct posicion));
					q->x = p->x;
					q->y = p->y + 1;
					q->sig = lista_posiciones;
					lista_posiciones = q;
				}
				if (p->x < columnas - 1) {
					if (tablero [p->y + 1][p->x + 1] & CUBIERTO)
					{
						q = malloc (sizeof (struct posicion));
						q->x = p->x + 1;
						q->y = p->y + 1;
						q->sig = lista_posiciones;
						lista_posiciones = q;
					}
				}
			}
		}
		free (p);
	}
}

/* fin de haz_jugada.c */
