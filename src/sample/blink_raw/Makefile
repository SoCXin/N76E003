.PHONY: all program

all: blink_raw.ihx

blink_raw.ihx: blink_raw.c
	sdcc -mmcs51 --out-fmt-ihx -o blink_raw.ihx blink_raw.c -I../include

program: blink_raw.ihx
	nuvoprog program -t n76e003 -a blink_raw.ihx -c @config.json -v
