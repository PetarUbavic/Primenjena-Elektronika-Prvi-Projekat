#include "Tajmeri.h"
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


#define TMR3_period 1000/*  Fosc = 10MHz,
					          1/Fosc = 0.1us !!!, 0.1us * 1000 = 100u  */



void Init_T3(void)
{
	TMR3 = 0;
	PR3 = TMR3_period;
	
	T3CONbits.TCS= 0; // 0 = Internal clock (FOSC/4)
	//IPC1bits.T2IP = 3 // T2 interrupt pririty (0-7)
	//SRbits.IPL = 3; // CPU interrupt priority is 3(11)
	IFS0bits.T3IF = 0; // clear interrupt flag
	IEC0bits.T3IE = 1; // enable interrupt

	T3CONbits.TON = 1; // T2 on 
}



//---------------------------------------
