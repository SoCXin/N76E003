/* SPDX-License-Identifier: GPL-3.0-or-later */
/* Copyright 2021, Frank Zago */

#include <stdint.h>

#include <n76e003.h>

static inline void nop(void)
{
	__asm__ ("nop");
}

/* Provide TA protection to use some special register. The expression
 * MUST compile to a single instruction. */
#define ta_prot(EXPR) do { TA = 0xaa; TA = 0x55; EXPR; } while(0)

/* MCU initialization. Should be called first by programs. */
void init_n76e(void);

/* Initializes UART0 */
void init_uart0(void);

/* Busy wait for the given amount of milliseconds */
void delay(uint16_t msec);

/* Enable / disable IAP. Must be disabled once access is over. */
static inline void iap_enable(void)
{
	__data uint8_t save_ea;

	save_ea = EA;
	EA = 0;
	ta_prot(CHPCON |= 1);
	EA = save_ea;
}

static inline void iap_disable(void)
{
	__data uint8_t save_ea;

	save_ea = EA;
	EA = 0;
	ta_prot(CHPCON &= ~1);
	EA = save_ea;
}

/* Use IAP to read a location */
uint8_t iap_read(enum ipa_modes mode, uint16_t addr);

/* WS2812 control. Call reset then send the colors in a loop. */
void ws_reset(void);
void ws_send_color(uint8_t R, uint8_t G, uint8_t B);

/* I2C */
struct i2c_op {
	uint8_t addr;		 /* 7-bit addr | R/W */
	volatile uint8_t len;	 /* significant data length in buffer */
	volatile uint8_t idx;	 /* current byte index in buf */
	volatile uint8_t status; /* I2C status, enum i2c_status */
	uint8_t *buf;		 /* read / write buffer */
};

/* This keeps the I2C state during operations. */
extern __xdata struct i2c_op i2c_op;
void init_i2c(void);
void i2c_enable_master(void);
int i2c_write(uint8_t len);
int i2c_read(uint8_t len);
void i2c_isr(void);

/* SPI */
void init_spi_master(uint8_t cpol, uint8_t cpha);
uint8_t spi_transfer(uint8_t value);
