/* $Id: error.c,v 1.5 2011/11/18 19:27:13 luis Exp $
 * error.c -- rutina para generar errores.
 * Autor: Luis Colorado
 * Version: 1.00 (30.1.93)
 */
#include <stdio.h>
#include <stdlib.h>

static char RCS_Id[] = "\n$Id: error.c,v 1.5 2011/11/18 19:27:13 luis Exp $\n";

void error (s)
char *s;
{
	printf("Error: %s\n", s);
	exit(1);
} /* error */

/* $Id: error.c,v 1.5 2011/11/18 19:27:13 luis Exp $ */
