/* SPDX-License-Identifier: GPL-3.0-or-later */
/* Copyright 2021, Frank Zago */

/* Visual effect with a WS2812-based LED strip.
 *
 * Connect the MCU to a strip.
 *   5V or 3.3V  <--> VCC
 *   GND         <--> GND
 *   WSPIN       <--> Data In, posssibly through a resistor
 *
 * There might be a bug somewhere as the first LED flickers.
 */

#include <stdint.h>

#include <libn76e.h>

#include "wheel.h"

/* Number of LEDS on the strip */
#define NB_LEDS 24

void main(void)
{
	int idx = 0;
	int led;

	init_n76e();

	while (1) {
		int wheel_idx = idx;

		ws_reset();

		for (led = 0; led < NB_LEDS; led++) {
			wheel_idx += 11;
			if (wheel_idx >= 768)
				wheel_idx -= 768;

			ws_send_color(wheel[wheel_idx].R, wheel[wheel_idx].G,
				      wheel[wheel_idx].B);
		}
		idx += 7;
		if (idx >= 768)
			idx -= 768;

		delay(20);
	}
}
