TOPTARGETS := all clean

SUBDIRS := \
	lib/ \
	examples/aht10 \
	examples/blink \
	examples/bmp280-i2c \
	examples/bmp280-spi \
	examples/iap \
	examples/max7219-matrix \
	examples/stepmotor \
	examples/uart \
	examples/wii-nunchuk \
	examples/ws2812

$(TOPTARGETS): $(SUBDIRS)
$(SUBDIRS):
	$(MAKE) -C $@ $(MAKECMDGOALS)

.PHONY: $(TOPTARGETS) $(SUBDIRS)
