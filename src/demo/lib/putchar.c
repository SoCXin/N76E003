/* SPDX-License-Identifier: GPL-3.0-or-later */
/* Copyright 2021, Frank Zago */

#include <stdio.h>

#include <libn76e.h>

int putchar(int c)
{
    while (!TI);
    TI = 0;
    SBUF = c;

    return c;
}
