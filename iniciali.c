/* $Id: iniciali.c,v 1.7 2014/04/10 13:03:16 luis Exp $
 * inicializa_tablero.c -- funcion para inicializar el tablero.
 * Autor: Luis Colorado.
 * Version: 1.00 (30.1.93)
 */

/*#include <malloc.h>*/
#include <stdlib.h>
#include <assert.h>
#include <getopt.h>
#include "tablero.h"

static char RCS_Id[] = "\n$Id: iniciali.c,v 1.7 2014/04/10 13:03:16 luis Exp $\n";

struct tablero *inicializa_tablero (int argc, char **argv)
{
	int res, i, j;
	int prob = PROBAB;
	int maxfilas = (LINES - 5),
		 maxcolumnas = (COLS - 3) / 2;
	int filas, columnas;

	randomize ();

	filas = maxfilas;
	columnas = maxcolumnas;
	while((res = getopt(argc, argv, "r:c:p:m")) != EOF) {
		switch(res) {
		case 'r': filas		= atoi(optarg);	break;
		case 'c': columnas	= atoi(optarg);	break;
		case 'p': prob			= atoi(optarg);	break;
		case 'm': filas		= maxfilas;
					 columnas	= maxcolumnas;		break;
		} /* switch */
	} /* while */

	if (filas < 1) filas = 1;
	if (filas > maxfilas) filas = maxfilas;
	if (columnas < 1) columnas = 1;
	if (columnas > maxcolumnas) columnas = maxcolumnas;
	if (prob < 1) prob = 1;
	if (prob > 99) prob = 99;

	/* creamos el tablero */
	return new_tablero(columnas, filas, prob);
}

/* $Id: iniciali.c,v 1.7 2014/04/10 13:03:16 luis Exp $ */
