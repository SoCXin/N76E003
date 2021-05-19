/* SPDX-License-Identifier: GPL-3.0-or-later */
/* Copyright 2021, Frank Zago */

/* Delay execution by a given number of milliseconds. */

#include <libn76e.h>

void delay(uint16_t msec)
{
	const uint16_t tick_per_ms = FSYS / 12 / 1000;
	const uint16_t start = ~tick_per_ms;

	/* Clock is Fsys / 12 */
	SET_FIELD(CKCON, T0M, 0);

	/* Set timer 0 in mode 1 */
	SET_FIELD(TMOD, T0M, 1);

	while (msec) {
		THL0 = start;

		TR0 = 1;

		while (TF0 == 0);

		TR0 = 0;
		TF0 = 0;

		msec--;
	}
}
