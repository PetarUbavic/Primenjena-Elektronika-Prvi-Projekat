#include <stdio.h>
#include "driverGLCD.h"
#include <stdlib.h>
#include "adc.h"
#include "Tajmeri.h"
#include "timer2.h"
#include "timer3.h"

#define servo LATDbits.LATD8

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
    if(U1MODEbits.PDSEL == 4) //3
        U1TXREG = data;
    else
        U1TXREG = data & 0xFF;
}

void RS232_putst(register const char*str)
{
    while((*str)!=0)
    {
        WriteUART1(*str);
        str++;
    }
}

/***************************************************************************
* Ime funkcije      : initUART1                                            *
* Opis              : inicjalizuje RS232 komunikaciju s 28800 bauda        * 
* Parameteri        : Nema                                                 *
* Povratna vrednost : Nema                                                 *
***************************************************************************/
void initUART1(void)
{
    //OVO JE KOPIRANO IZ Touch screen.X
    U1BRG=0x0015; //ovim odredjujemo baudrate
    U1MODEbits.ALTIO=0; //biramo koje pinove koristimo za komunikaciju osnovne ili alternativne, koristimo alternativne

    IEC0bits.U1RXIE = 1;
    U1STA&=0xfffc;
    U1MODEbits.UARTEN=1;
    U1STAbits.UTXEN=1;
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

void ispisiPir(unsigned int pir) // ispisuje na terminal vrednost AD konverzije sa PIR-a
{
    RS232_putst("  PIR: ");
    WriteUART1dec2string(pir);
	//for(int broj1=0;broj1<1000;broj1++);
}
void ispisiMq3(unsigned int mq3) // ispisuje na terminal vrednost AD konverzije sa MQ3
{
    RS232_putst("  MQ3: ");
	WriteUART1dec2string(mq3);
    //for(int broj1=0;broj1<1000;broj1++);
}

void ispisiFoto(unsigned int foto) // ispisuje na terminal vrednost AD konverzije sa fotootoprnika
{
    RS232_putst("  FOTO: ");
    WriteUART1dec2string(foto);
	//for(int broj1=0;broj1<1000;broj1++);
}
