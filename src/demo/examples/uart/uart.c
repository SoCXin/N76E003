/* SPDX-License-Identifier: GPL-3.0-or-later */
/* Copyright 2021, Frank Zago */

/* Output some strings on UART0. */

#include <stdio.h>

#include <libn76e.h>

void main(void)
{
	init_n76e();
	init_uart0();

	puts("I'm alive!!!");

	while (1) {
		/* Blink too for good measure */
		delay(1000);
		LED_BUILTIN = !LED_BUILTIN;

		puts("I'm still alive!!!");
	}
}
