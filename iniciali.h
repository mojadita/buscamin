/* iniciali.h -- interface to inicializa_tablero.
 * Author: Luis Colorado <lc@luiscoloradosistemas.com>Q
 * Date: mié abr  9 12:22:45 CEST 2014
 * Disclaimer: (C) 1993-2025 Luis Colorado.  All rights reserved.
 * License: BSD
 */
#ifndef _INICIALI_H
#define _INICIALI_H

#include "tablero.h"

struct tablero *
inicializa_tablero (
        int    argc,
        char **argv);

#endif /* _INICIALI_H */
