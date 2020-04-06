//-------------------------------------------------------------------
// main.c - Initalize GPIO and USARTS to output a string to visualize on the scope
//
// Uses Zhu's SysClock code to init system clocks
//
// Textbook reference - page 534 (22.1) and Appendix I
// copyright zhu, Gregory Huras, Caleb Hoeksema
//-------------------------------------------------------------------
#include "VirtualPort.h"

int main(void){

	System_Clock_Init();
	VIRTUAL_PORT_INIT();

	// Run loop continueously
	while(1){
		UARTprintf("Greg "); // Runs UARTprintf function which output each character out of the GPIO
		
		for(unsigned int i = 0; i < 100000; i++); // This loop runs and acts as a 100 ms delay
	}
	
} //main()
