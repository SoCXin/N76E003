.PHONY: all program

all: hello_uart_raw.ihx

hello_uart_raw.ihx: hello.c
	sdcc -mmcs51 --out-fmt-ihx -o hello_uart_raw.ihx hello.c -I../include

program: hello_uart_raw.ihx
	nuvoprog program -t n76e003 -a hello_uart_raw.ihx -c @config.json -v
