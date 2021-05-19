/* SPDX-License-Identifier: GPL-3.0-or-later */
/* Copyright 2021, Frank Zago */

/* Simple display on an 8x8 LED matrix driven by a MAX7219
 *
 * Clear the screen, and turn each LED on one by one at 25ms interval, forever.
 *
 * Pinout:
 *  Matrix   Host
 *  ------   ----
 *  VCC      3.3V
 *  GND      GND
 *  DIN      P00 - MOSI
 *  CS       P15 - SS but could be another pin
 *  CLK      P10 - SPCLK
 *
 * As per its datasheet, the MAX7219 needs 4V minimum, but it seems to
 * work well enough with the 3.3V provided by the N76E003.
 */

#include <stdio.h>
#include <string.h>
#include <stdint.h>

#include <libn76e.h>

/* Write a 2 bytes command: register and data */
static void cmd(uint8_t reg, uint8_t data)
{
	/* Slave select */
	SS = 0;

	spi_transfer(reg);
	spi_transfer(data);

	/* Slave deselect */
	SS = 1;
}

/* Clear all lines */
static void clear(void)
{
    int i;

    for (i = 1; i <= 8; i++)
	    cmd(i, 0);
}

void main(void)
{
	int i;
	int j;

	init_n76e();

	/* Deselect slave */
	SS = 1;

	/* Mode 0. */
	init_spi_master(0, 0);

	/* Initialize the MAX7219. See datasheet. */
	cmd(0x0c, 0x00);
	cmd(0x0b, 0x07);
	cmd(0x0a, 0x00);
	cmd(0x0f, 0x00);
	cmd(0x09, 0x00);
	clear();
	cmd(0x0c, 0x01);

	while (1) {
		for (i = 0; i < 8; i++) {
			uint8_t val = 0;

			for (j = 0; j < 8; j++) {
				val |= 1 << j;
				cmd(0x01 + i, val);
				delay(25);
			}
		}

		delay(1000);
		clear();
	}
}
