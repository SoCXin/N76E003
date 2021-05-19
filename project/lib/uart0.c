/* SPDX-License-Identifier: GPL-3.0-or-later */
/* Copyright 2021, Frank Zago */

#include <libn76e.h>

/* UART library. Initializes UART0 to 111111b/s. In the future this
 * could also change the clock to 16.6MHz as described in section 13.5
 * of the datasheet to do real 115200 b/s.
 */
void init_uart0(void)
{
	SCON = 0;
	REN = 1;
	SM1 = 1;
	TI = 1;

	SET_FIELD(TMOD, T1M, 2);   /* mode 2 */
	SET_FIELD(PCON, SMOD, 1);  /* double baud rate */
	SET_FIELD(CKCON, T1M, 1);  /* system clock is source */
	SET_FIELD(T3CON, BRCK, 0); /* select time 1 */

	/* This defines the baud rate, 111111b/s when running at 16MHz */
	TH1 = (uint8_t)(256 - (FSYS / 16 / 115200 + 1));

	TR1 = 1;
}
