/* defs.h -- fichero con definiciones para el juego del buscaminas.
 * Autor: Luis Colorado.
 * Version: 1.00 (30.1.93)
 */

#include <curses.h>
#include <stdio.h>

#ifndef NULL
#define NULL 0
#endif

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
#define MASCARA		0x0f

#define PROBAB		15	/* la probabilidad de mina */

#define randomize() srand (time (0))
#define random(N) (rand () % (N))

/* fin de defs.h */
