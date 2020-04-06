#ifndef _VIRTUALPORT_H
#define _VIRTUALPORT_H

#include "SysClock.h"
#include "stm32l476xx.h"
#include <stdarg.h>
#include <stdio.h>

void VIRTUAL_PORT_INIT(void);
void Virtual_UARTinit(void);

#define F_PD5_PD6 			(0xF << (2*5))	
#define AF_PD5_PD6 			(0x77<<(4*5))
#define MODER_PD5_PD6 	(0xA<<(2*5))
#define OTYPER_PD5_PD6 	(0x3<<5)
#define PUPDR_PD5_PD6 	(0x5<<(2*5))


#define MAX_UART_BUFSIZ 40
void UARTputs( char *str );
void UARTputc(char cx);
void UARTprintf(char *fmt, ...);

#endif
