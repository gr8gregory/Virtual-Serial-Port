/*
The virtual port can be monitored thorugh applications like tera-term or putty.
To see through tera-term, download and open the application, then just click on the 
serial button and select the correct port which should say STM 32--- etc. 

This code uses USART2 and PD5 and PD6 for rx and tx. The code is taken and modified from
GPIO code as well as UART code from previous labs. The code uses the UART printf functions
to print to the port

Gregory Huras 2020
*/

#include "VirtualPort.h"
#include "utils.h"

void VIRTUAL_PORT_INIT(void){
	
	RCC->AHB2ENR |= RCC_AHB2ENR_GPIODEN;
	// PD6 - TX
	// PD5 - RX

	// 00 = Input, 01 = Output, 10 = Alternate Function, 11 = Analog
	// Clear mode bits for pin 5 and 6 
	// Select Alternate Function Mode (10)
	CLR_BITS(GPIOD->MODER, F_PD5_PD6);
	SET_BITS(GPIOD->MODER, MODER_PD5_PD6);
	
	// Alternate funiton 7 = USART1
	// Appendix I Shows all alternate function (Page 700)
	GPIOD->AFR[0] |= AF_PD5_PD6;		// Set pin 5 and 6 to AF 7
	
	
	// GPIO Speed:	00 = Low speed, 	01 = Medium Speed
	// 							10 = Fast speed, 	11 = high speed
	SET_BITS(GPIOD->OSPEEDR, F_PD5_PD6);
	
	// GPIO Push-pull:	00 = No pull-up/pull-down	01 = pull-up
	// 									10 = pull-down						11 = reserved
	// Select pull-up
	CLR_BITS(GPIOD->PUPDR, F_PD5_PD6);
	SET_BITS(GPIOD->PUPDR, PUPDR_PD5_PD6);
	
	
	// GPIO output type: 0 = push-pull, 1 = open drain
	CLR_BITS(GPIOD->OTYPER, OTYPER_PD5_PD6);
	
	// Enable USART2 Clock
	SET_BITS(RCC->APB1ENR1, RCC_APB1ENR1_USART2EN);
	
	//Set the USART2 Clock Frequency
	CLR_BITS(RCC->CCIPR, RCC_CCIPR_USART2SEL);
	SET_BITS(RCC->CCIPR, RCC_CCIPR_USART2SEL_0);
	
	
	Virtual_UARTinit();
}


// This initializaes the USARTs
void Virtual_UARTinit(void){
	
	USART2->CR1 &= ~USART_CR1_UE;						//Disable UE port
	USART2->CR1 &= ~USART_CR1_M;
	
	USART2->CR2 &= ~USART_CR2_STOP;
	USART2->CR1 &= ~USART_CR1_PCE;
	USART2->CR1 &= ~USART_CR1_OVER8;

	USART2->BRR = 0x208D;
	
	USART2->CR1 |= (USART_CR1_TE | USART_CR1_RE);
	
	USART2->CR1 |= USART_CR1_UE;
	
	while((USART2->ISR & USART_ISR_TEACK)==0);
	
	while((USART2->ISR & USART_ISR_REACK) == 0);
	
	// do stuff
}


void UARTprintf(char *fmt, ...){
	va_list args;
	
	char buffer[MAX_UART_BUFSIZ];

	va_start( args, fmt);
	vsnprintf( buffer, MAX_UART_BUFSIZ, fmt, args);
	va_end(args);
	
	UARTputs(buffer);
	
}

void UARTputc(char cx){
	while (!(USART2-> ISR & USART_ISR_TXE));	//Waits until the hardware is ready
	USART2-> TDR = (uint8_t)cx;								// Dumps the data out
}

void UARTputs( char *str ){
	
	while (*str){
			UARTputc( *str++);
	}
	
}
