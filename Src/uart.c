#include "uart.h"


void init_gpio_TX(){
	// set clock of PA9
	MODIFY_REG(RCC->AHB1ENR,
				RCC_AHB1ENR_GPIOAEN,
				_VAL2FLD(RCC_AHB1ENR_GPIOAEN, 0x1));

	// set output mode for PA9
	MODIFY_REG(GPIOA->MODER,
				GPIO_MODER_MODE9,
				_VAL2FLD(GPIO_MODER_MODE9, 0x2));

	// set AFRH9 as AF7
	MODIFY_REG(GPIOA->AFR[1],
				GPIO_AFRH_AFSEL9,
				_VAL2FLD(GPIO_AFRH_AFSEL9, 7));

}


void init_gpio_RX(){
	// set clock of PA10

	// set output mode for PA10
	MODIFY_REG(GPIOA->MODER,
				GPIO_MODER_MODE10,
				_VAL2FLD(GPIO_MODER_MODE10, 0x2));

	// set AFRH10 as AF7
	MODIFY_REG(GPIOA->AFR[1],
				GPIO_AFRH_AFSEL10,
				_VAL2FLD(GPIO_AFRH_AFSEL10, 7));

}

void init_uart(){

	// enable clk for USART
	MODIFY_REG(RCC->APB2ENR,
				RCC_APB2ENR_USART1EN,
				_VAL2FLD(RCC_APB2ENR_USART1EN, 0x1));

	// enable USART	| UE = 1
	MODIFY_REG(USART1->CR1,
				USART_CR1_UE,
				_VAL2FLD(USART_CR1_UE, 0x1));

	// program M-bit
	MODIFY_REG(USART1->CR1,
				USART_CR1_M,
				_VAL2FLD(USART_CR1_M, 0x0));

	// set stop bits in CR2
	MODIFY_REG(USART1->CR2,
				USART_CR2_STOP,
				_VAL2FLD(USART_CR2_STOP, 0x0));

	// set the baud rate
	MODIFY_REG(USART1->BRR,
				USART_BRR_DIV_Mantissa | USART_BRR_DIV_Fraction,
				_VAL2FLD(USART_BRR_DIV_Mantissa , 8) | _VAL2FLD(USART_BRR_DIV_Fraction, 11));

	// set TE in CR1 | TE = 1
	MODIFY_REG(USART1->CR1,
				USART_CR1_TE,
				_VAL2FLD(USART_CR1_TE, 0x1));

	// set TE in CR1 | RE = 1
	MODIFY_REG(USART1->CR1,
				USART_CR1_RE,
				_VAL2FLD(USART_CR1_RE, 0x1));

}



void sendChar(char c){
	MODIFY_REG(USART1->DR,
				USART_DR_DR,
				_VAL2FLD(USART_DR_DR, c));
	while(!READ_BIT(USART1->SR , USART_SR_TC));
}

uint16_t UART_read(){

	while(!READ_BIT(USART1->SR, USART_SR_RXNE));
	uint16_t c = READ_REG(USART1->DR);
	if (READ_BIT(USART1->SR, USART_SR_ORE)) {
		CLEAR_BIT(USART1->SR, USART_SR_ORE);
	}
	return c;

}

void UART_write(const char *str){
	if(*str == '\0'){
		return;
	}
	for(int i=0;str[i]!='\0';i++){
		sendChar(str[i]);
	}
}


void init_UART(){
	init_uart();
	init_gpio_TX();
	init_gpio_RX();
	init_gpio_TX();
	init_gpio_RX();
}

