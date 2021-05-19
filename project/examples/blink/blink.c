/* SPDX-License-Identifier: GPL-3.0-or-later */
/* Copyright 2021, Frank Zago */

/* Blink the builtin LED. 500ms off, 1s on. */

#include <stdint.h>

#include <libn76e.h>

void main(void)
{
	init_n76e();

	while (1) {
		LED_BUILTIN = 0;
		delay(500);
		LED_BUILTIN = 1;
		delay(1000);
	}
}
