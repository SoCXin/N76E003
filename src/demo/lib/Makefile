include ../config.mk

CFLAGS += -I../include

all: libn76.lib

libn76.lib: init.o delay.o uart0.o putchar.o iap.o ws2812.o i2c.o bmp280.o spi.o
	sdar -rc $@ $^

%.o: %.c ../include/libn76e.h ../include/n76e003.h
	sdcc $(CFLAGS) -mmcs51 -c -o $@ $< -I../include

clean:
	rm -f *.o libn76.lib *.map *.mem *.rst *.lk *.lst *.rel  *.sym *.asm
