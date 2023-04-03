#include<p30fxxxx.h>

#include "adc.h"



void ConfigureADCPins(void)
{
	ADPCFGbits.PCFG0=0;
    ADPCFGbits.PCFG6=1; // dioda spoljnjeg tipa
    TRISBbits.TRISB6=0; // izlaz za diodu spoljnjeg tipa
    
	/*ADPCFGbits.PCFG9=0;
     
    ADPCFGbits.PCFG6=0;//pir
    ADPCFGbits.PCFG7=0;//mq3
    ADPCFGbits.PCFG12=0; //foto
    */
    
    //TRISDbits.TRISD9 = 1; // ulaz za interupt
    //TRISAbits.TRISA11 = 1; // ulaz za interupt
	
    
	TRISBbits.TRISB0=1;
    TRISDbits.TRISD0=0; //pwm za pogon motora 
    TRISDbits.TRISD1=0; //pwm za pogon motora
    
    TRISAbits.TRISA11=1; //ulaz za echo interupt prvi
    TRISDbits.TRISD9=1; //ulaz za echo interupt drugi
    
    
    TRISFbits.TRISF0=0; //za smer motora
    TRISFbits.TRISF1=0; // za smer drugog motora

    TRISBbits.TRISB10=0; // za smer drugog motora
    TRISBbits.TRISB11=0; // za smer drugog motora
    TRISBbits.TRISB2 = 0; //triger
   // TRISBbits.TRISB3 = 1; //echo
   // ADPCFGbits.PCFG3 = 1; //echo pin digitalni
    
    ADPCFGbits.PCFG10=1; //
    ADPCFGbits.PCFG11=1; //
    
    /*
	TRISBbits.TRISB9=1;
    TRISFbits.TRISF6=0;
    
    TRISBbits.TRISB6=1;
    TRISBbits.TRISB7=1;
    TRISBbits.TRISB12=1;
    
    TRISFbits.TRISF2=1;/* za selekt tastere F2,
                          
    
    TRISDbits.TRISD9=0;
    */
}

void ADCinit(void)
{

ADCON1bits.ADSIDL=0;
ADCON1bits.FORM=0;
ADCON1bits.SSRC=7;
//na kraju  ADCON1bits.ASAM=1;
ADCON1bits.SAMP=1;
//ADCON1bits.ADON=1;      //ovo na kraju


ADCON2bits.VCFG=7;
ADCON2bits.CSCNA=1;
ADCON2bits.SMPI=2;
ADCON2bits.BUFM=0;
ADCON2bits.ALTS=0;



ADCON3bits.SAMC=31;
ADCON3bits.ADRC=1;
ADCON3bits.ADCS=31;

ADCHSbits.CH0NB=0;
ADCHSbits.CH0NA=0;

ADCHSbits.CH0SA=0;
ADCHSbits.CH0SB=0;

ADPCFG=0; 


/*ADCSSL: A/D Input Scan Select Register

bit 15-0 CSSL<15:0>: A/D Input Pin Scan Selection bits
	1 = Select ANx for input scan
	0 = Skip ANx for input scan*/
//ADCSSL=0b0001111111111111;

    ADCSSL=0b0000000000000001;
  //ADCSSL=0b0001001001111111; //koristimo 6 7 i 12 6pir 7mq3 12foto
         //  FEDCBA9876543210
                  
  
ADCON1bits.ASAM=1;

IFS0bits.ADIF=1;
IEC0bits.ADIE=1;
}