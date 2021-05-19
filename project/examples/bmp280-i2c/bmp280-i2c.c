/* SPDX-License-Identifier: GPL-3.0-or-later */
/* Copyright 2021, Frank Zago */

/* Read from GY-BMP280 module, using I2C.
 *
 * Pinout:
 *  BMP280  Host
 *  ------  ----
 *  VCC     3.3V
 *  GND     GND
 *  SCL     P13 - SCL
 *  SDA     P14 - SDA
 *  CSB     not connected
 *  SDO     GND (to select address 0x76)
 */

#include <stdio.h>
#include <string.h>
#include <stdint.h>

#include <libn76e.h>
#include <bmp280.h>

void bmp280_i2c_isr(void) __interrupt (INT_I2C)
{
	i2c_isr();
}

/* Read a one byte register value. Return 0 on success, 1 on error. */
static int bmp_read(uint8_t reg, int len)
{
	int rc;

	i2c_op.buf[0] = reg;
	rc = i2c_write(1);

	if (rc)
		return 1;

	/* Read result */
	rc = i2c_read(len);

	return rc;
}

/* Write to a register. Data must start at buf[1]. */
static int bmp_write(uint8_t reg, int len)
{
	i2c_op.buf[0] = reg;
	return i2c_write(1 + len);
}

void main(void)
{
	const uint8_t sla_addr = bmp280_addr1;
	__xdata union {
		/* At most 6 bytes will be read, or 2 written */
		uint8_t buf[6];

		/* For writing */
		struct {
			uint8_t reg;
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
	init_i2c();
	i2c_enable_master();

	puts("Addressing the BMP280");

	/* Initialize i2c op */
	i2c_op.addr = sla_addr << 1;
	i2c_op.buf = bmp280_data.buf;

	/* Read device ID */
	if (bmp_read(REG_ID, 1) != 0) {
		puts("Can't read ID");
		goto done;
	}

	if (bmp280_data.r.id != 0x58) {
		puts("BMP280 not found at given address");
		goto done;
	}

	/* Read calibration in another buffer */
	i2c_op.buf = (void *)&calib;
	if (bmp_read(REG_CAL_MIN, REG_CAL_MAX - REG_CAL_MIN + 1)) {
		puts("Can't read calibration data");
		goto done;
	}

	i2c_op.buf = bmp280_data.buf;

	/* Configure the device according to Android entry,
	 *   Table 15: Sensor timing according to recommended settings */
	bmp280_data.buf[1] = 0;
	bmp280_data.w.config.filter = 4;
	bmp280_data.w.config.t_sb = 0b001; /* 62.5ms */
	if (bmp_write(REG_CONFIG, 1)) {
		puts("Can't set config register");
		goto done;
	}

	bmp280_data.buf[1] = 0;
	bmp280_data.w.ctrl_meas.mode = 0b11;    /* normal, see 3.6 Power modes */
	bmp280_data.w.ctrl_meas.osrs_p = 0b101; /* x16, see 3.3.2 Temperature measurement */
	bmp280_data.w.ctrl_meas.osrs_t = 0b010; /* x2, see 3.3.1 and 4.3.4 */
	if (bmp_write(REG_CTRL_MEAS, 1)) {
		puts("Can't set control register");
		goto done;
	}

	while (1) {
		int32_t output;

		/* Read temperature and pressure in burst mode */
		if (bmp_read(REG_PRESS_MSB, 6) != 0) {
			puts("Can't get temperature");
			goto done;
		}

		/* Temperature must go first because of t_fine calculation */
		output = bmp280_to_20bits(&i2c_op.buf[3]);
		output = bmp280_compensate_T_int32(output, &calib);
		printf("Temperature: %lu.%02lu °C\n", output / 100, output % 100);

		output = bmp280_to_20bits(&i2c_op.buf[0]);
		output = bmp280_compensate_P_int32(output, &calib);
		printf("Pressure: %lu Pa\n", output);

		delay(1000);
	}

done:
	puts("Looping forever");
	while(1)
		delay(1000);
}
