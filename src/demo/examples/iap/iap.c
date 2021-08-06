/* SPDX-License-Identifier: GPL-3.0-or-later */
/* Copyright 2021, Frank Zago */

/* Use the IAP to read the MCU UID, company ID and device ID */

#include <stdio.h>

#include <libn76e.h>

void main(void)
{
    char uid[12];
    int i;

    init_n76e();
    init_uart0();

    while (1) {
	/* Blink LED too */
	LED_BUILTIN = !LED_BUILTIN;

	iap_enable();

	printf("UID ");
	for (i = 0; i < 12; i++) {
	    uid[i] = iap_read(READ_UID, i);
	    printf("%02x:", uid[i]);
	}
	puts("");

	/* Should be 0x3650 for N76E003 */
	printf("Device ID 0x%02x%02x\n", iap_read(DID_READ, 1), iap_read(DID_READ, 0));

	/* Should be 0xda */
	printf("Company ID 0x%02x\n", iap_read(CID_READ, 0));

	iap_disable();

	delay(2000);
    }
}
