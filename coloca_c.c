/* coloca_cursor.c -- rutina para colocar el cursor en la posicion ade-
 *	cuada.
 * Autor: Luis Colorado.
 * Version: 1.00 (30.1.93)
 */

#include "defs.h"

void coloca_cursor ()
{
	move (pos_y + 2, 2*pos_x + 3);
	refresh ();
}

/* fin de coloca_cursor.c */
