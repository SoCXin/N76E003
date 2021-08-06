/* SPDX-License-Identifier: GPL-3.0-or-later */
/* Copyright 2021, Frank Zago */

#include <stdint.h>

#include <libn76e.h>

/* Send a byte on the bus. The timing seems to work well for the 16MHz
 * clock. */
static void ws_write_byte(uint8_t val)
{
	int i;

	for (i = 0; i < 8; i++) {
		if ((val << i) & 0x80) {
			WS_PIN = 1;
			nop();
			nop();
			nop();
			nop();
			WS_PIN = 0;
			nop();
			nop();
		} else {
			WS_PIN = 1;
			nop();
			nop();
			WS_PIN = 0;
			nop();
			nop();
			nop();
			nop();
		}
	}
}

/* Send a full color to an LED */
void ws_send_color(uint8_t R, uint8_t G, uint8_t B)
{
	ws_write_byte(G);
	ws_write_byte(R);
	ws_write_byte(B);
}

void ws_reset(void)
{
	WS_PIN = 0;

	/* This needs at least 50μs for the old models, and 280μs for the
	 * new ones. */
	delay(1);
}
