/* error.c -- rutina para generar errores.
 * Autor: Luis Colorado
 * Version: 1.00 (30.1.93)
 */

void error (s)
char *s;
{
	printf ("Error: %s\n", s);
	exit (1);
}
