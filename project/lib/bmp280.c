/* The data conversion code is extracted from the BMP280 datasheet, rev 1.23 */

#include <libn76e.h>

#include <bmp280.h>

static __xdata int32_t t_fine;

/* Return the temperature in 1/100 °C. Code is from the BMP280
 * datasheet. */
int32_t bmp280_compensate_T_int32(int32_t adc_T, const struct bmp280_calib *c)
{
	__xdata int32_t var1;

	var1 = ((((adc_T >> 3) - ((int32_t)c->dig_T1 << 1))) * ((int32_t)c->dig_T2)) >> 11;
	var1 += (((((adc_T >> 4) - ((int32_t)c->dig_T1)) * ((adc_T >> 4) - ((int32_t)c->dig_T1))) >> 12) *
		((int32_t)c->dig_T3)) >> 14;
	t_fine = var1;
	var1 *= 5;
	var1 += 128;
	var1 >>= 8;

	return var1;
}

/* Returns pressure in Pa as unsigned 32 bit integer. Output value of
 * “96386” equals 96386 Pa = 963.86 hPa. Code is from the BMP280
 * datasheet.
 *
 * Note that t_fine is set by bmp280_compensate_T_int32, so that
 * function should be called first.
 */
uint32_t bmp280_compensate_P_int32(int32_t adc_P, const struct bmp280_calib *c)
{
	__xdata int32_t var1, var2;
	__xdata uint32_t p;

	var1 = ((t_fine)>>1) - (int32_t)64000;
	var2 = (((var1>>2) * (var1>>2)) >> 11 ) * ((int32_t)c->dig_P6);
	var2 = var2 + ((var1*((int32_t)c->dig_P5))<<1);
	var2 = (var2>>2)+(((int32_t)c->dig_P4)<<16);

	var1 = (((c->dig_P3 * (((var1>>2) * (var1>>2)) >> 13 )) >> 3) + ((((int32_t)c->dig_P2) * var1)>>1))>>18;
	var1 =((((32768+var1))*((int32_t)c->dig_P1))>>15);
	if (var1 == 0) {
		return 0; /* avoid exception caused by division by zero */
	}
	p = (((uint32_t)(((int32_t)1048576)-adc_P)-(var2>>12)))*3125;
	if (p < 0x80000000) {
		p = (p << 1) / ((uint32_t)var1);
	} else {
		p = (p / (uint32_t)var1) * 2;
	}
	var1 = (((int32_t)c->dig_P9) * ((int32_t)(((p>>3) * (p>>3))>>13)))>>12;
	var2 = (((int32_t)(p>>2)) * ((int32_t)c->dig_P8))>>13;
	p = (uint32_t)((int32_t)p + ((var1 + var2 + c->dig_P7) >> 4));

	return p;
}

/* Convert 3 bytes into 20 bits value. */
uint32_t bmp280_to_20bits(const unsigned char *val)
{
	__xdata int32_t value;

	value = val[0];
	value <<= 8;
	value |= val[1];
	value <<= 8;
	value |= val[2];
	value >>= 4;

	return value;
}
