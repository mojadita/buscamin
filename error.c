/* $Id: error.c,v 1.3 2001/12/24 01:24:51 luis Exp $
 * error.c -- rutina para generar errores.
 * Autor: Luis Colorado
 * Version: 1.00 (30.1.93)
 */

static char RCS_Id[] = "\n$Id: error.c,v 1.3 2001/12/24 01:24:51 luis Exp $\n";

void error (s)
char *s;
{
	printf ("Error: %s\n", s);
	exit (1);
}

/* $Id: error.c,v 1.3 2001/12/24 01:24:51 luis Exp $ */
