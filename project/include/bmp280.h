/* SPDX-License-Identifier: GPL-3.0-or-later */
/* Copyright 2021, Frank Zago */

/* Derived from the BMP280 spec */

enum bmp280_regs {
	REG_TEMP_XLSB = 0xfc,
	REG_TEMP_LSB = 0xfb,
	REG_TEMP_MSB = 0xfa,
	REG_PRESS_XLSB = 0xf9,
	REG_PRESS_LSB = 0xf8,
	REG_PRESS_MSB = 0xf7,
	REG_CONFIG = 0xf5,
	REG_CTRL_MEAS = 0xf4,
	REG_STATUS = 0xf3,
	REG_RESET = 0xe0,
	REG_ID = 0xd0,
	REG_CAL_MAX = 0x9f,		/* 0xa0/0xa1 is reserved so skip it */
	REG_CAL_MIN = 0x88,
};

struct bmp280_status {
	uint8_t im_update : 1;
	uint8_t _unused2  : 2;
	uint8_t measuring : 1;
	uint8_t _unused1  : 4;
};

struct bmp280_config {
	uint8_t spi3w_en : 1;
	uint8_t _unused  : 1;
	uint8_t filter   : 3;
	uint8_t t_sb     : 3;
};

struct bmp280_ctrl_meas {
	uint8_t mode   : 2;
	uint8_t osrs_p : 3;
	uint8_t osrs_t : 3;
};

enum bmp280_addresses {
	bmp280_addr1 = 0x76,
	bmp280_addr2 = 0x77,
};

struct bmp280_calib {
	uint16_t dig_T1;
	int16_t dig_T2;
	int16_t dig_T3;
	uint16_t dig_P1;
	int16_t dig_P2;
	int16_t dig_P3;
	int16_t dig_P4;
	int16_t dig_P5;
	int16_t dig_P6;
	int16_t dig_P7;
	int16_t dig_P8;
	int16_t dig_P9;
};

/* BMP280 helpers */
int32_t bmp280_compensate_T_int32(int32_t adc_T, const struct bmp280_calib *c);
uint32_t bmp280_compensate_P_int32(int32_t adc_P, const struct bmp280_calib *c);
uint32_t bmp280_to_20bits(const unsigned char *val);
