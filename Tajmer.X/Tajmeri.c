//#include "tajmeri.h"
#include <p30fxxxx.h>


#define TMR2_period 1000/*  Fosc = 10MHz,
					          1/Fosc = 0.1us !!!, 0.1us * 10000 = 1ms  */


void Init_T2(void)
{
	TMR2 = 0;
	PR2 = TMR2_period;
	
	T2CONbits.TCS = 0; // 0 = Internal clock (FOSC/4)
	//IPC1bits.T2IP = 3 // T2 interrupt pririty (0-7)
	//SRbits.IPL = 3; // CPU interrupt priority is 3(11)
	IFS0bits.T2IF = 0; // clear interrupt flag
	IEC0bits.T2IE = 1; // enable interrupt

	T2CONbits.TON = 1; // T2 on 
}

//---------------------------------------
