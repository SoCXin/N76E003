/* SPDX-License-Identifier: GPL-3.0-or-later */
/* Copyright 2021, Frank Zago */

/* I2C support.
 *
 * For now only the default ports are supported. It could be possible
 * to create a second bus on the P02/P16 pins.
*/

#include <string.h>

#include <libn76e.h>

#define I2C_ACK_R 1		/* R/W bit in address field */

enum i2c_status {
	I2C_ST_INIT,
	I2C_ST_EINVAL,
	I2C_ST_WR_OK,
	I2C_ST_RD_OK,
	I2C_ST_ERROR,
};

/* I2C state machine. */
__xdata struct i2c_op i2c_op;

void init_i2c(void)
{
	memset(&i2c_op, 0, sizeof(i2c_op));

	/* P13, P14 in open-drain mode */
	P1M1 |= (1 << 3);
	P1M2 |= (1 << 3);

	P1M1 |= (1 << 4);
	P1M2 |= (1 << 4);

	/* Try to clear bus if needed */
	while (I2CSI != 0) {
		if (I2STAT == 0x00)
			I2CSTO = 1;

		I2CSI = 0;
		if (I2CSI != 0)	{
			I2CEN = 0;
			I2CEN = 1;
			I2CSI = 0;
			I2CEN = 0;
		}
		delay(10);
	}
}

/* Enable I2C in master mode */
void i2c_enable_master(void)
{
	/* Master mode */
	SDA = 1;
	SCL = 1;
	I2CLK = 9;		/* Default. 400kb/s at 16MHz */

	/* Enable interrupts */
	EIE |= EIE_EI2C_BIT;
	EA = 1;

	I2CEN = 1;
}

/* Interrupt driven state machine */
void i2c_isr(void)
{
	switch (I2STAT)	{
	case I2CSTAT_BUS_ERROR:
		I2CSTO = 1;
		break;

	case I2CSTAT_M_START:
	case I2CSTAT_M_REPEAT_START:
		I2CSTA = 0;
		I2DAT = i2c_op.addr;
		break;

	case I2CSTAT_M_TX_ADDR_ACK:
		/* Write byte */
		I2DAT = i2c_op.buf[i2c_op.idx];
		i2c_op.idx++;
		break;

	case I2CSTAT_M_TX_ADDR_NACK:
		I2CSTO = 1;
		I2CAA = 1;
		i2c_op.status = I2C_ST_ERROR;
		break;

	case I2CSTAT_M_TX_DATA_ACK:
		if (i2c_op.idx < i2c_op.len) {
			/* Write next byte */
			I2DAT = i2c_op.buf[i2c_op.idx];
			i2c_op.idx++;
		} else {
			/* All bytes written. Success. */
			I2CSTO = 1;
			I2CAA = 1;
			i2c_op.status = I2C_ST_WR_OK;
		}
		break;

	case I2CSTAT_M_TX_DATA_NACK:
		I2CSTO = 1;
		I2CAA = 1;
		i2c_op.status = I2C_ST_ERROR;
		break;

	case I2CSTAT_M_ARB_LOST:
		/* Another master is currently present. Try again. */
		I2CSTA = 1;
		break;

	case I2CSTAT_M_RX_ADDR_ACK:
		if (i2c_op.len == 1)
			I2CAA = 0;
		else
			I2CAA = 1;
		break;

	case I2CSTAT_M_RX_ADDR_NACK:
		I2CSTO = 1;
		I2CAA = 1;
		break;

	case I2CSTAT_M_RX_DATA_ACK:
		/* Store received byte */
		i2c_op.buf[i2c_op.idx] = I2DAT;
		i2c_op.idx++;
		i2c_op.len--;
		if (i2c_op.len == 1)
			I2CAA = 0;
		else
			I2CAA = 1;
		break;

	case I2CSTAT_M_RX_DATA_NACK:
		/* Last byte received */
		i2c_op.buf[i2c_op.idx] = I2DAT;
		i2c_op.idx++;
		i2c_op.len--;
		I2CSTO = 1;
		I2CAA = 1;
		i2c_op.status = I2C_ST_RD_OK;
		break;
	}

	I2CSI = 0;

	while (I2CSTO);
}

int i2c_write(uint8_t len)
{
	i2c_op.len = len;
	i2c_op.addr &= ~I2C_ACK_R;	/* Write */
	i2c_op.status = I2C_ST_INIT;
	i2c_op.idx = 0;

	I2CSTA = 1;			/* start */

	while (i2c_op.status == I2C_ST_INIT);

	return i2c_op.status != I2C_ST_WR_OK;
}

int i2c_read(uint8_t len)
{
	i2c_op.len = len;
	i2c_op.addr |= I2C_ACK_R;	/* Read */
	i2c_op.status = I2C_ST_INIT;
	i2c_op.idx = 0;

	I2CSTA = 1;			/* start */

	while (i2c_op.status == I2C_ST_INIT);

	return i2c_op.status != I2C_ST_RD_OK;
}
