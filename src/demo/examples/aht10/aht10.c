/* SPDX-License-Identifier: GPL-3.0-or-later */
/* Copyright 2021, Frank Zago */

/*
 * AHT10/AHT15 and possibly AHT20/21/25
 *
 * The datasheet is incomplete.
 *
 *  AHT     Host
 *  ------  ----
 *  1       3.3V
 *  2       P14 - SDA
 *  3       GND
 *  4       P13 - SCL
 */

#include <stdio.h>
#include <string.h>
#include <stdint.h>

#include <libn76e.h>

#define INIT_CMD 0b11100001
#define TRIG_CMD 0b10101100
#define RESET_CMD 0b10111010

struct aht_data {
	uint8_t reserved1  : 3;
	uint8_t calibrated : 1;
	uint8_t reserved   : 1;
	uint8_t mode       : 2;
	uint8_t busy       : 1;

	/* 20 bits for humidity, followed by 20 bits for temperature. */
	uint8_t data[5];
};

void ahtxx_i2c_isr(void) __interrupt (INT_I2C)
{
	i2c_isr();
}

void main(void)
{
	const uint8_t sla_addr = 0x38;
	uint8_t buf[6]; /* At most 6 bytes will be read, or 3 written */
	struct aht_data *aht_data = (void *)buf;
	int rc;
	uint32_t temp;
	uint32_t hum;

	init_n76e();
	init_uart0();
	init_i2c();
	i2c_enable_master();

	puts("Addressing the AHT10/15");

	/* Initialize i2c op */
	i2c_op.addr = sla_addr << 1;
	i2c_op.buf = buf;

	/* Initialize the AHT */
	buf[0] = INIT_CMD;
//	buf[1] = 0b10101100;	/* from spec but doesn't work with AHT15 */
	buf[1] = 0b00101000;	/* from linux kernel. Adafruit uses 0x8. */
	buf[2] = 0;		/* other implementations have this. not in spec */
	rc = i2c_write(3);
	if (rc)
		goto done;

	/* Read data every second */
	while (1) {
		buf[0] = TRIG_CMD;
		buf[1] = 0b00110011; /* datasheet magic number */
		buf[2] = 0;

		rc = i2c_write(3);
		if (rc)
			goto done;

		delay(65);	/* delay 75ms (65+10). */

		do {
			delay(10);

			rc = i2c_read(6);
			if (rc)
				goto done;

		} while (aht_data->busy);

		/* Rebuild humidity, and apply integer formula, from
		 * linux kernel */
		hum = buf[1];
		hum <<= 8;
		hum |= buf[2];
		hum <<= 4;
		hum |= buf[3] >> 4;

		hum *= 625;
		hum >>= 16;
		hum *= 10;

		/* Rebuild temperature, and apply integer formula from
		 * linux kernel */
		temp = buf[3] & 0x0f;
		temp <<= 8;
		temp |= buf[4];
		temp <<= 8;
		temp |= buf[5];

		temp *= 625;
		temp >>= 15;
		temp *= 10;
		temp -= 50000;

		printf("temp=%ld.%03ld, humidity=%ld.%03ld%%\n",
		       temp / 1000, temp % 1000,  hum / 1000, hum % 1000);

		delay(1000);
	}

done:
	puts("Error - looping forever");
	while (1)
		delay(1000);
}
