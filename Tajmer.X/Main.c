#include <stdio.h>
#include <stdlib.h>
//#include <p30fxxxx.h>
#include "adc.h"
#include "Tajmeri.h"

_FOSC(CSW_FSCM_OFF & XT_PLL4);//instruction takt je isti kao i kristal 10MHz
_FWDT(WDT_OFF);


unsigned int pir,mq3,foto, enpir, enfoto;
unsigned int broj,broj1,broj2,tempRX;

unsigned int brojac_ms,stoperica,ms,sekund;

/***************************************************************************
* Ime funkcije      : initUART1                                            *
* Opis              : inicjalizuje RS232 komunikaciju s 9600bauda          * 
* Parameteri        : Nema                                                 *
* Povratna vrednost : Nema                                                 *
***************************************************************************/

void initUART1(void)
{
U1BRG=0x0040;//baud rate 9600
U1MODEbits.ALTIO = 1;
IEC0bits.U1RXIE = 1;
U1STA&=0xfffc;
U1MODEbits.UARTEN=1;
U1STAbits.UTXEN=1;
}
void __attribute__((__interrupt__, no_auto_psv)) _U1RXInterrupt(void) 
{
    IFS0bits.U1RXIF = 0;
  //   tempRX=U1RXREG;
} 

void __attribute__((__interrupt__, no_auto_psv)) _ADCInterrupt(void) 
{
	pir=ADCBUF0;
	mq3=ADCBUF1;
	foto=ADCBUF2;									

    IFS0bits.ADIF = 0;
} 

/*********************************************************************
* Ime funkcije      : WriteUART1                            		 *
* Opis              : Funkcija upisuje podatke u registar U1TXREG,   *
*                     za slanje podataka    						 *
* Parameteri        : unsigned int data-podatak koji zelimo poslati  *
* Povratna vrednost : Nema                                           *
*********************************************************************/

void WriteUART1(unsigned int data)
{
	while (U1STAbits.TRMT==0);
    if(U1MODEbits.PDSEL == 3)
        U1TXREG = data;
    else
        U1TXREG = data & 0xFF;
}
/***********************************************************************
* Ime funkcije      : WriteUART1dec2string                     		   *
* Opis              : Funkcija salje 4-cifrene brojeve (cifru po cifru)*
* Parameteri        : unsigned int data-podatak koji zelimo poslati    *
* Povratna vrednost : Nema                                             *
************************************************************************/
void WriteUART1dec2string(unsigned int data)
{
	unsigned char temp;

	temp=data/1000;
	WriteUART1(temp+'0');
	data=data-temp*1000;
	temp=data/100;
	WriteUART1(temp+'0');
	data=data-temp*100;
	temp=data/10;
	WriteUART1(temp+'0');
	data=data-temp*10;
	WriteUART1(data+'0');
}


void ispisiPir(unsigned int pir)
{
    WriteUART1('P');WriteUART1('I');WriteUART1('R');WriteUART1(' ');
    WriteUART1dec2string(pir);
	for(broj2=0;broj2<1000;broj2++);
}

void ispisiMq3(unsigned int mq3)
{
    WriteUART1(' ');WriteUART1('M');WriteUART1('Q');WriteUART1('3');WriteUART1(' ');
	WriteUART1dec2string(mq3);
    for(broj2=0;broj2<1000;broj2++);
}

void ispisiFoto(unsigned int foto)
{
    WriteUART1(' ');WriteUART1('F');WriteUART1('O');WriteUART1('T');WriteUART1(' ');
    WriteUART1dec2string(foto);
	for(broj2=0;broj2<1000;broj2++);
}

unsigned int detektujPrilaz(unsigned int pir)
{
    if(pir > 2000)
        {
            enpir++;
            if(enpir % 2 == 1)
                enfoto = 1;
                /// dodati watchdog timer ili nesto slicno
            else
                enfoto = 0;
        }
    return enfoto;
}


void __attribute__ ((__interrupt__, no_auto_psv)) _T2Interrupt(void) // svakih 1ms
{
	TMR2 =0;
     ms=1;//fleg za milisekundu ili prekid;potrebno ga je samo resetovati u funkciji

	brojac_ms++;//brojac milisekundi
    stoperica++;//brojac za funkciju Delay_ms

    if (brojac_ms==1000)//sek
        {
          brojac_ms=0;
          sekund=1;//fleg za sekundu
		 } 
	IFS0bits.T2IF = 0;    
}


void Delay_ms (int vreme)//funkcija za kasnjenje u milisekundama
	{
		stoperica = 0;
		while(stoperica < vreme);
	}
/*
 * 
 */

void servo0()
{
    LATBbits.LATB5 = 1;
    Delay_ms(5);
    LATBbits.LATB5 = 0;
    Delay_ms(195);
}

void servo90()
{
    LATBbits.LATB5 = 1;
    Delay_ms(15);
    LATBbits.LATB5 = 0;
    Delay_ms(185); 
}

void servo180()
{
    LATBbits.LATB5 = 1;
    Delay_ms(40);
    LATBbits.LATB5 = 0;
    Delay_ms(160);
}

int main(int argc, char** argv) {
    
    for(broj1=0;broj1<10000;broj1++);

		TRISBbits.TRISB0=1;//ulazni pin pir
		TRISBbits.TRISB1=1;//ulazni pin mq3
        TRISBbits.TRISB2=1;//ulazni pin fotootpornik
        TRISBbits.TRISB5=0;//izlazni pin

		for(broj=0;broj<60000;broj++);

		initUART1();//inicijalizacija UART-a
 		ADCinit();//inicijalizacija AD konvertora

		ADCON1bits.ADON=1;//pocetak Ad konverzije 
        
        Init_T2();
        
        
	while(1)
	{
        ispisiPir(pir);
        ispisiMq3(mq3);
        ispisiFoto(foto);
		WriteUART1(13);//enter
                
        servo0();
	}//od whilea

    return (EXIT_SUCCESS);
}