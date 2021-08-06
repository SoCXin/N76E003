/* SPDX-License-Identifier: GPL-3.0-or-later */
/* Copyright 2021, Frank Zago */

/* Read from GY-BMP280 module, using SPI.
 *
 * Pinout:
 *  BMP280   Host
 *  ------   ----
 *  VCC     3.3V
 *  GND     GND
 *  SCL     P10 - SPCLK
 *  SDA     P00 - MOSI
 *  CSB     P15 - SS but could be another pin
 *  SDO     P01 - MISO
 */

#include <stdio.h>
#include <string.h>
#include <stdint.h>

#include <libn76e.h>
#include <bmp280.h>

/* Read a one byte register value. Return 0 on success, 1 on error. */
static int bmp_read(uint8_t reg, uint8_t *buf, int len)
{
	int idx = 0;

	/* Slave select */
	SS = 0;

	/* Highest bit must be 1 to tell the BMP280 it's a read. */
	spi_transfer(reg | 0x80);

	while (len) {
		/* The value to write doesn't matter */
		buf[idx++] = spi_transfer(0);
		len--;
	}

	/* Slave deselect */
	SS = 1;

	return 0;
}

/* Read a one byte register value. Return 0 on success, 1 on error. */
static int bmp_write(uint8_t reg, uint8_t *buf, int len)
{
	int idx = 0;

	/* Slave select */
	SS = 0;

	/* Highest bit must be 0 to tell the BMP280 it's a write. */
	spi_transfer(reg & 0x7f);

	while (len) {
		/* The value read doesn't matter */
		spi_transfer(buf[idx++]);
		len--;
	}

	/* Slave deselect */
	SS = 1;

	return 0;
}

void main(void)
{
	__xdata union {
		/* At most 6 bytes will be read, or 2 written */
		uint8_t buf[6];

		/* For writing */
		struct {
			union {
				struct bmp280_config config;
				struct bmp280_ctrl_meas ctrl_meas;
			};
		} w;

		union {
			uint8_t id;
			struct bmp280_config config;
			struct bmp280_status status;

		} r;
	} bmp280_data;
	__xdata struct bmp280_calib calib;

	init_n76e();
	init_uart0();

	/* Deselect slave */
	SS = 1;

	/* The BMP280 supports modes 00 and 11. Pick one. */
	init_spi_master(0, 0);

	/* Read device ID */
	if (bmp_read(REG_ID, bmp280_data.buf, 1) != 0) {
		puts("Can't read ID");
		goto done;
	}

	if (bmp280_data.r.id != 0x58) {
		puts("BMP280 not found at given address");
		goto done;
	}

	/* Read calibration in another buffer */
	if (bmp_read(REG_CAL_MIN, (void *)&calib, REG_CAL_MAX - REG_CAL_MIN + 1)) {
		puts("Can't read calibration data");
		goto done;
	}

	/* Configure the device according to Android entry,
	 *   Table 15: Sensor timing according to recommended settings */
	bmp280_data.buf[0] = 0;
	bmp280_data.w.config.filter = 4;
	bmp280_data.w.config.t_sb = 0b001; /* 62.5ms */
	if (bmp_write(REG_CONFIG, bmp280_data.buf, 1)) {
		puts("Can't set config register");
		goto done;
	}

	bmp280_data.buf[0] = 0;
	bmp280_data.w.ctrl_meas.mode = 0b11;    /* normal, see 3.6 Power modes */
	bmp280_data.w.ctrl_meas.osrs_p = 0b101; /* x16, see 3.3.2 Temperature measurement */
	bmp280_data.w.ctrl_meas.osrs_t = 0b010; /* x2, see 3.3.1 and 4.3.4 */
	if (bmp_write(REG_CTRL_MEAS, bmp280_data.buf, 1)) {
		puts("Can't set control register");
		goto done;
	}

	while (1) {
		int32_t output;

		/* Read temperature and pressure in burst mode */
		if (bmp_read(REG_PRESS_MSB, bmp280_data.buf, 6) != 0) {
			puts("Can't get temperature");
			goto done;
		}

		/* Temperature must go first because of t_fine calculation */
		output = bmp280_to_20bits(&bmp280_data.buf[3]);
		output = bmp280_compensate_T_int32(output, &calib);
		printf("Temperature: %lu.%02lu °C\n", output / 100, output % 100);

		output = bmp280_to_20bits(&bmp280_data.buf[0]);
		output = bmp280_compensate_P_int32(output, &calib);
		printf("Pressure: %lu Pa\n", output);

		delay(1000);
	}

done:
	puts("Looping forever");
	while(1)
		delay(1000);
}
