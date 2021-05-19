NAME=bmp280-i2c
ISP_OPTS += -s

all: $(NAME).bin
	cp $(NAME).bin ../../build

include ../../Rules.mk

$(NAME).c: $(TOPDIR)/include/bmp280.h
