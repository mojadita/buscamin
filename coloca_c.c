/* $Id: coloca_c.c,v 1.3 2001/12/24 01:24:51 luis Exp $
 * coloca_cursor.c -- rutina para colocar el cursor en la posicion ade-
 *	cuada.
 * Autor: Luis Colorado.
 * Version: 1.00 (30.1.93)
 */

#include "defs.h"

static char RCS_Id[] = "\n$Id: coloca_c.c,v 1.3 2001/12/24 01:24:51 luis Exp $\n";

void coloca_cursor ()
{
	move (pos_y + 2, 2*pos_x + 3);
	refresh ();
}

/* $Id: coloca_c.c,v 1.3 2001/12/24 01:24:51 luis Exp $ */
