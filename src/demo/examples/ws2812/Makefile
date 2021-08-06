NAME=ws2812

all: $(NAME).bin
	cp $(NAME).bin ../../build

include ../../Rules.mk

$(NAME).c: wheel.h

wheel.h:
	./gen_data.py
