/* SPDX-License-Identifier: GPL-3.0-or-later */
/* Copyright 2021, Frank Zago */

/* Read from a Nintendo Wii Nunchuk
 * The Nunchuk is a 3V device, with 1.8KΩ pullup resistors on SDL and SDA.
 *
 * Pinout with a cheap breakout board:
 *  Nunchuk  Host
 *  ------  ----
 *  +       3.3V
 *  -       GND
 *  C       P13 - SCL
 *  D       P14 - SDA
 *
 * Hardcoded address is 0x52.
 *
 * Protocol comes from various sources, including:
 *   https://bootlin.com/labs/doc/nunchuk.pdf
 *   https://www.hackster.io/infusion/using-a-wii-nunchuk-with-arduino-597254#toc-calibration-8
 *   https://wiibrew.org/wiki/Wiimote/Extension_Controllers
 */

#include <stdio.h>
#include <string.h>
#include <stdint.h>

#include <libn76e.h>

void nunchuk_i2c_isr(void) __interrupt (INT_I2C)
{
	i2c_isr();
}

struct nunchuck_data {
	uint8_t joy_x;
	uint8_t joy_y;
	uint8_t accel_x;
	uint8_t accel_y;
	uint8_t accel_z;
	uint8_t but_z : 1;
	uint8_t but_c : 1;
	uint8_t accel_x_low : 2;
	uint8_t accel_y_low : 2;
	uint8_t accel_z_low : 2;
};

void main(void)
{
	const uint8_t sla_addr = 0x52;
	uint8_t buf[16]; /* At most 16 bytes will be read, or 2 written */
	const struct nunchuck_data *data = (void *)buf;
	int rc;
	int i;

	init_n76e();
	init_uart0();
	init_i2c();
	i2c_enable_master();

	puts("Addressing the nunchuk");

	/* Initialize i2c op */
	i2c_op.addr = sla_addr << 1;
	i2c_op.buf = buf;

	/* Setup the Nunchuk in non-encrypted mode */
	buf[0] = 0xf0;
	buf[1] = 0x55;
	rc = i2c_write(2);
	if (rc)
		goto done;

	delay(10);

	buf[0] = 0xfb;
	buf[1] = 0x00;
	rc = i2c_write(2);
	if (rc)
		goto done;

	delay(100);

	/* Read device type
	 *   00 00 a4 20 00 00 is nunchuk.
	 * Other values are possible. See wiibrew.org page. */
	buf[0] = 0xfa;
	rc = i2c_write(1);
	if (rc)
		goto done;

	rc = i2c_read(6);
	if (rc)
		goto done;

	puts("device type:");
	for (i = 0; i < 6; i++)
		printf("%02x ", buf[i]);
	puts("");

	/* Read calibration */
	buf[0] = 0x20;
	rc = i2c_write(1);
	if (rc)
		goto done;

	rc = i2c_read(16);
	if (rc)
		goto done;

	puts("calibration data:\n");
	for (i = 0; i < 16; i++)
		printf("%02x ", buf[i]);
	puts("");

	/* Read data */
	while (1) {
		buf[0] = 0x00;
		rc = i2c_write(1);
		if (rc)
			goto done;

		rc = i2c_read(6);
		if (rc)
			goto done;

		puts("Nunchuk raw data");
		for (i = 0; i < 6; i++)
			printf("%02x ", buf[i]);
		puts("");

		printf("  Joystick position: %u, %u\n", data->joy_x, data->joy_y);
		printf("  Accel: %u, %u, %u\n",
		       data->accel_x << 2 | data->accel_x_low,
		       data->accel_y << 2 | data->accel_y_low,
		       data->accel_z << 2 | data->accel_z_low);

		if (!((struct nunchuck_data *)buf)->but_z)
			puts("  Z pressed");

		if (!((struct nunchuck_data *)buf)->but_c)
			puts("  C pressed");

		puts("");

		delay(1000);
	}

done:
	puts("Error - looping forever");
	while(1)
		delay(1000);
}
