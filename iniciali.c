/* $Id: iniciali.c,v 1.4 2002/01/18 14:08:50 luis Exp $
 * inicializa_tablero.c -- funcion para inicializar el tablero.
 * Autor: Luis Colorado.
 * Version: 1.00 (30.1.93)
 */

#include <malloc.h>
#include <stdlib.h>
#include <getopt.h>
#include "defs.h"

static char RCS_Id[] = "\n$Id: iniciali.c,v 1.4 2002/01/18 14:08:50 luis Exp $\n";

void inicializa_tablero (argc, argv)
int argc;
char **argv;
{
	int res, i, j;
	int prob = PROBAB;
	int maxfilas = (LINES - 5), maxcolumnas = (COLS - 5) / 2;
	randomize ();

	while((res = getopt(argc, argv, "l:c:p:m")) != EOF) {
		switch(res) {
		case 'l': filas = atoi(optarg); break;
		case 'c': columnas = atoi(optarg); break;
		case 'p': prob = atoi(optarg); break;
		case'm': filas = maxfilas; columnas = maxcolumnas; break;
		} /* switch */
	} /* while */
	if (filas < 1) filas = 1;
	if (filas > maxfilas) filas = maxfilas;
	if (columnas < 1) columnas = 1;
	if (columnas > maxcolumnas) columnas = maxcolumnas;
	if (prob < 1) prob = 1;
	if (prob > 99) prob = 99;

	/* creamos el tablero */
	tablero = malloc (filas * sizeof (char *));
	for (i = 0; i < filas; i++) {
		tablero [i] = malloc (columnas * sizeof (char));
		for (j = 0; j < columnas; j++) {
			res = random (100) < prob;
			if (res) {
				tablero [i][j] = MINA | CUBIERTO;
				num_minas++;
			} else {
				tablero [i][j] = CUBIERTO;
			}
		}
	}
	/* inicializamos los valores de las variables */
	for (i = 0; i < filas; i++) {
		for (j = 0; j < columnas; j++) {
			if (i > 0) {
				if (j > 0) {
					if (tablero [i-1][j-1] & MINA)
						tablero [i][j]++;
				}
				if (tablero [i-1][j] & MINA)
					tablero [i][j]++;
				if (j < columnas - 1) {
					if (tablero [i-1][j+1] & MINA)
						tablero [i][j]++;
				}
			}
			if (j > 0) {
				if (tablero [i][j-1] & MINA)
					tablero [i][j]++;
			}
			if (j < columnas - 1) {
				if (tablero [i][j+1] & MINA)
					tablero [i][j]++;
			}
			if (i < filas - 1) {
				if (j > 0) {
					if (tablero [i+1][j-1] & MINA)
						tablero [i][j]++;
				}
				if (tablero [i+1][j] & MINA)
					tablero [i][j]++;
				if (j < columnas - 1) {
					if (tablero [i+1][j+1] & MINA)
						tablero [i][j]++;
				}
			}
		} /* for j */
	} /* for i */
	quedan = filas * columnas - num_minas;
	printf ("num_minas == %d\n", num_minas);
}

/* $Id: iniciali.c,v 1.4 2002/01/18 14:08:50 luis Exp $ */
