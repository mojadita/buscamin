/* $Id: iniciali.c,v 1.3 2001/12/24 01:24:51 luis Exp $
 * inicializa_tablero.c -- funcion para inicializar el tablero.
 * Autor: Luis Colorado.
 * Version: 1.00 (30.1.93)
 */

#include <malloc.h>
#include <stdlib.h>
#include "defs.h"

static char RCS_Id[] = "\n$Id: iniciali.c,v 1.3 2001/12/24 01:24:51 luis Exp $\n";

void inicializa_tablero (argc, argv)
int argc;
char **argv;
{
	int res, i, j;
	int prob = PROBAB;
	randomize ();
	argc--; argv++;
	if (argc > 0) {  /* tama¤o del tablero */
		res = sscanf (argv [0], "%d", &prob);
		if (res != 1)
			error ("Primer parametro incorrecto");
		if (prob < 0) {
			prob = - prob;
			argc--; argv++;
		} else {
			prob = PROBAB;
		}
	}
	printf ("PROBABILIDAD DE MINA == %d\n", prob);
	if (argc > 0) {
		if (argc < 2)
			error ("Pocos parametros (falta una dimension)");
		res = sscanf (argv [0], "%d", &filas);
		if (res != 1)
			error ("Numero de filas incorrecto");
		res = sscanf (argv [1], "%d", &columnas);
		if (res != 1)
			error ("Numero de columnas incorrecto");
		argc -= 2; argv += 2;
	}
	if (argc > 0) error ("Demasiados parametros");
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

/* $Id: iniciali.c,v 1.3 2001/12/24 01:24:51 luis Exp $ */
