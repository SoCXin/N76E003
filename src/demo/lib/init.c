/* SPDX-License-Identifier: GPL-3.0-or-later */
/* Copyright 2021, Frank Zago */

#include <libn76e.h>

void init_n76e(void)
{
	/* Errata. Disable POR */
	ta_prot(PORDIS = 0X5A);
	ta_prot(PORDIS = 0XA5);

	/* Set all pins in quasi-bidirectional mode */
	P0M1 = 0;
	P0M2 = 0;
	P1M1 = 0;
	P1M2 = 0;
	P3M1 = 0;
	P3M2 = 0;
}
