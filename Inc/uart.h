#ifndef UART_H_
#define UART_H_

#define STM32F401xE
#include <stdint.h>
#include "stm32f4xx.h"				// for bitwise operations
#include "stm32f401xe.h"
#include "system_stm32f4xx.h"


void UART_write(const char *str);
uint16_t UART_read();
void sendChar(char c);
void init_UART();

#endif /* UART_H_ */
