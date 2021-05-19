/* SPDX-License-Identifier: GPL-3.0-or-later */
/* Copyright 2021, Frank Zago */

#include <stdio.h>
#include <string.h>
#include <stdint.h>

#include <libn76e.h>

void init_spi_master(uint8_t cpol, uint8_t cpha)
{
	/* Set SS pin as regular pin. It is not special in master mode.
	 * Table 14-1. Slave Select Pin Configurations
	 */
	SET_FIELD(SPSR, DISMODF, 1);
	SET_FIELD(SPCR, SSOE, 0);

	/* Configure clock profile */
	SET_FIELD(SPCR, CPHA, cpha);
	SET_FIELD(SPCR, CPOL, cpol);
	SET_FIELD(SPCR, SPR, 0); /* 8Mbit/s */

	SET_FIELD(SPCR, MSTR, 1);

	SET_FIELD(SPCR, SPIEN, 1);
}

/* Transfer a value and return the slave's value. The caller must have
 * enabled the slave's chip select. */
uint8_t spi_transfer(uint8_t value)
{
	SPDR = value;
	while (!(SPSR & 0x80));
	SET_FIELD(SPSR, SPIF, 0);

	return SPDR;
}
