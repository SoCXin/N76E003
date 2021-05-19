NAME=ws2812

all: $(NAME).bin

include ../../Rules.mk

$(NAME).c: wheel.h

wheel.h:
	./gen_data.py
