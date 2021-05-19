/* SPDX-License-Identifier: GPL-3.0-or-later */
/* Copyright 2021, Frank Zago */

#include <stdint.h>

#include <libn76e.h>

/* Table 21-1. IAP Modes and Command Codes. IAP must be enabled first. */
uint8_t iap_read(enum ipa_modes mode, uint16_t addr)
{
	__data uint8_t save_ea;

	IAPCN = mode;
	IAPA = addr;

	save_ea = EA;
	EA = 0;
	ta_prot(IAPTRG |= 1);
	EA = save_ea;

	return IAPFD;
}
