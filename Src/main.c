#include <stdint.h>
#include "stdio.h"
#include "uart.h"

int main(void)
{
	init_UART();
	while(1){
		uint16_t c = UART_read();
		sendChar(c);
		//UART_write("Hello world\n");
	}
}
