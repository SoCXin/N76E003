TOPDIR := $(dir $(lastword $(MAKEFILE_LIST)))

include $(TOPDIR)/config.mk

CFLAGS += -I$(TOPDIR)/include/
LDLIBS += $(TOPDIR)/lib/libn76.lib

$(NAME).bin: $(NAME).ihx
	makebin -p $^ $@

$(NAME).ihx: $(NAME).c $(LDLIBS)
	sdcc $(CFLAGS) -mmcs51 --out-fmt-ihx -o $@ $^ $(LDLIBS)

isp: $(NAME).bin
	nvtispflash -a $^ $(ISP_OPTS)

clean:
	rm -f *.bin *.ihx $(NAME).map $(NAME).mem $(NAME).rst $(NAME).lk \
		$(NAME).lst $(NAME).rel $(NAME).sym $(NAME).asm
