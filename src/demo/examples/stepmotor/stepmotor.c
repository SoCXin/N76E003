/* SPDX-License-Identifier: GPL-3.0-or-later */
/* Copyright 2021, Frank Zago */

/* Drive a 5V 28BYJ-48 step motor with a ULN2003AN module.
 *
 * Pinout:
 *   N76  <-->      ULN    <-->  28BYJ-48
 *   ---            ---          --------
 *   P01        IN-1 / OUT1      blue (4)
 *   P02        IN-2 / OUT2      pink (2)
 *   P03        IN-3 / OUT3      yellow (3)
 *   P04        IN-4 / OUT4      orange (1)
 *
 * plus 5V to ULN and motor, and common ground for all.
 *
 * The motor is programmed in half-steps. There are 4096 half-steps in
 * a revolution.
 *
 * This example uses a 1ms delay between each half-steps, which gives
 * about one rotation per 4s, or 15rpm.
 */

#include <stdint.h>
#include <stdbool.h>

#include <libn76e.h>

/* Current half-step */
uint8_t step;

/* Define which N76E003 pins correspond to the UNL. */
#define blue P01
#define pink P02
#define yellow P03
#define orange P04

/* For the next step, de-energize the now unused coil from either side
 * of the current step, then energize the new coil. See the numerous
 * documentation on that motor for the logic behind the half-steps. */
static void next_step(bool clockwise)
{
	switch (step & 0x7) {
	case 0:
		blue = 1;
		yellow = 1;
		orange = 0;
		break;
	case 1:
		orange = 0;
		yellow = 0;
		break;
	case 2:
		pink = 1;
		orange = 1;
		yellow = 0;
		break;
	case 3:
		yellow = 0;
		pink = 0;
		break;
	case 4:
		yellow = 1;
		blue = 1;
		pink = 0;
		break;
	case 5:
		blue = 0;
		pink = 0;
		break;
	case 6:
		orange = 1;
		pink = 1;
		blue = 0;
		break;
	case 7:
		blue = 0;
		orange = 0;
		break;
	}

	if (clockwise)
		step--;
	else
		step++;
}

/* De-energize the coils. None of the doc mention shutting down the
 * motor that way, but it seems quite logical to save power.
 * Also that might be a good idea to call that function after each
 * step has been performed, but that'd require knowing how long to
 * wait for the motor to perform its movement. */
static void stop_motor(void)
{
	blue = 1;
	pink = 1;
	yellow = 1;
	orange = 1;
}

void main(void)
{
	int i;

	init_n76e();

	stop_motor();

	/* Could start anywhere. */
	step = 0;

	while (1) {
		/* Half a turn clockwise */
		for (i = 0; i < 2048; i++) {
			delay(1);
			next_step(true);
		}

		stop_motor();

		delay(1000);

		/* Half a turn counter-clockwise */
		for (i = 0; i < 2048; i++) {
			delay(1);
			next_step(false);
		}

		stop_motor();

		delay(2000);
	}
}
