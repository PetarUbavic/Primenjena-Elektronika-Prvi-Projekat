#include <stdio.h>
#include "driverGLCD.h"
#include <stdlib.h>
#include "adc.h"
#include "Tajmeri.h"
#include "timer2.h"
#include "timer3.h"
#include <stdbool.h> 
#include <outcompare.h>
//#include <p30fxxxx.h>

_FOSC(CSW_FSCM_OFF & XT_PLL4);//instruction takt je isti kao i kristal 10MHz
_FWDT(WDT_OFF);
_FGS(CODE_PROT_OFF);

//const unsigned int ADC_THRESHOLD = 900; 
const unsigned int AD_Xmin = 220;
const unsigned int AD_Xmax = 3642;
const unsigned int AD_Ymin = 520;
const unsigned int AD_Ymax = 3450;

unsigned int sirovi0,sirovi1;
unsigned int broj,broj1,broj2,temp0,temp1;

//#define DRIVE_A PORTBbits.RB10
//#define DRIVE_B PORTCbits.RC13
#define DRIVE_A PORTCbits.RC13
#define DRIVE_B PORTCbits.RC14

#define servo LATDbits.LATD8

#define pocetna 500

unsigned int X, Y,x_vrednost, y_vrednost;

unsigned int pir,mq3,foto, enpir, enfoto, enmq3;
unsigned int broj,broj1,broj2;

unsigned int brojac_ms,stoperica,ms,sekund;
unsigned int brojac_ms3,stoperica3,ms3,sekund3;

int korak = pocetna/5;
int vreme_on = pocetna;
int vreme_off = pocetna;


unsigned int morzeI=0;
unsigned int morzeBrojac=0;
unsigned int x;
unsigned int stanje, taster;
unsigned int niz[3];
unsigned char sifra[3];
unsigned char sifraProvera;
char r=1;
bool y;

unsigned char zakljucan = 0;
unsigned char tempRX;
unsigned int n;
int rec[5];

unsigned char /*const*/ tasteri_bmp[1024] = {
   0,  0,  0,  0,  0,  0,  0,240, 16, 16, 16, 16, 16, 16, 16, 16, 
  16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 
  16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16,240,  0,  0,  0,  0, 
   0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
   0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,240, 16, 16, 
  16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16,144, 16, 16, 16, 
  16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16,240,  0,  0,  0,  0, 
   0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
   0,  0,  0,  0,  0,  0,  0,255,  0,  0,  0,  0,  0,  0,  0,  0, 
  30, 18, 18, 18,226,  0,  0, 18,146, 78, 32,200, 36, 34,192,  0, 
   0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,255,  0,  0,  0,  0, 
   0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
   0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,255,  0,  0, 
   0,  0,  0,  0,  0,  0,  0, 32, 48, 40,228,  2,  1,  1,  2,228, 
  40, 48, 32,  0,  0,  0,  0,  0,  0,  0,  0,255,  0,  0,  0,  0, 
   0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
   0,  0,  0,  0,  0,  0,  0,127, 64, 64, 64, 64, 64, 64, 64, 64, 
  65, 65, 65, 65, 64, 64, 64, 64, 64, 64, 64, 64, 65, 65, 64, 64, 
  64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64,127,  0,  0,  0,  0, 
   0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
   0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 63, 32, 32, 
  32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 47, 40, 40, 40, 40, 47, 
  32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 63,  0,  0,  0,  0, 
   0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
   0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
   0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
   0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
   0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
   0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,128,128,128, 
 128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128, 
 128,128,128,128,128,128,128,128,128,128,128,128,  0,  0,  0,  0, 
   0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
   0,  0,  0,  0,  0,  0,  0,254,  2,  2,  2,  2,  2,  2,  2,  2, 
   2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2, 
   2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,254,  0,  0,  0,  0, 
   0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
   0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,255,  0,  0, 
   0,  0,  0,  0,  0,  0,  0,  0,  0,252,  4,  4,  4,  4,252,  0, 
   0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,255,  0,  0,  0,  0, 
   0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
   0,  0,  0,  0,  0,  0,  0,255,  0,  0,  0,130,130,255,128,128, 
   0,  0,126,129,129,129,102,  0,  0,  9, 73, 39, 16,100,146,145, 
  96,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,255,  0,  0,  0,  0, 
   0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
   0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,255,  0,  0, 
   0,  0,  0,  0,  0,  0,  0,  6, 10, 51, 64,128,  0,128, 67, 50, 
  10,  6,  0,  0,  0,  0,  0,  0,  0,  0,  0,255,  0,  0,  0,  0, 
   0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
   0,  0,  0,  0,  0,  0,  0, 15,  8,  8,  8,  8,  8,  8,  8,  8, 
   8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8, 
   8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8, 15,  0,  0,  0,  0, 
   0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
   0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 15,  8,  8, 
   8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  9, 10,  9,  8,  8, 
   8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8, 15,  0,  0,  0,  0, 
   0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
   0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
   0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
   0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
   0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
   0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
   0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
   0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
   0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0 
};


void Delay(unsigned int N)
{
	unsigned int i;
	for(i=0;i<N;i++);
}

void ConfigureTSPins(void)
{
	//ADPCFGbits.PCFG10=1;
	//ADPCFGbits.PCFG7=digital;

	//TRISBbits.TRISB10=0;
	TRISCbits.TRISC13=0;
    TRISCbits.TRISC14=0;
	
	//LATCbits.LATC14=0;
	//LATCbits.LATC13=0;
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
    U1BRG=0x0015;//ovim odredjujemo baudrate
    U1MODEbits.ALTIO=0;//biramo koje pinove koristimo za komunikaciju osnovne ili alternativne

    //U1BRG=0x0040;//baud rate 9600
    // U1MODEbits.ALTIO = 1; //OVO JE NA 1 ZA UART
    IEC0bits.U1RXIE = 1;
    U1STA&=0xfffc;
    U1MODEbits.UARTEN=1;
    U1STAbits.UTXEN=1;
}

void __attribute__((__interrupt__, no_auto_psv)) _U1RXInterrupt(void) 
{
    IFS0bits.U1RXIF = 0;
    tempRX=U1RXREG;
    
    if(tempRX != 0)
    {  
       rec[n] = tempRX;
       if(n < 5)
           n++;
       else n=0;
    }
} 

void __attribute__((__interrupt__, no_auto_psv)) _ADCInterrupt(void) 
{   	
	sirovi0=ADCBUF2;//0
	sirovi1=ADCBUF3;//1

	temp0=sirovi0;
	temp1=sirovi1;
       
	pir=ADCBUF0;
	mq3=ADCBUF1;
    foto=ADCBUF4;									

    IFS0bits.ADIF = 0;
} 


void Delay_ms (int vreme)//funkcija za kasnjenje u milisekundama
{
    stoperica = 0;
	while(stoperica < vreme);
}

void Delay_ms3 (int vreme)//funkcija za kasnjenje u milisekundama
{
	stoperica3 = 0;
	while(stoperica3 < vreme);
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

void Touch_Panel (void)
{
    // vode horizontalni tranzistori
	DRIVE_A = 1;  
	DRIVE_B = 0;
    
    LATCbits.LATC13=1;
    LATCbits.LATC14=0;

	Delay_ms(50); //cekamo jedno vreme da se odradi AD konverzija
				
	// ocitavamo x	
	x_vrednost = temp0;//temp0 je vrednost koji nam daje AD konvertor na BOTTOM pinu		

	// vode vertikalni tranzistori
    LATCbits.LATC13=0;
    LATCbits.LATC14=1;
	DRIVE_A = 0;  
	DRIVE_B = 1;

	Delay_ms(50); //cekamo jedno vreme da se odradi AD konverzija bilo 50
	
	// ocitavamo y	
	y_vrednost = temp1;// temp1 je vrednost koji nam daje AD konvertor na LEFT pinu	
	
    //Ako zelimo da nam X i Y koordinate budu kao rezolucija ekrana 128x64 treba skalirati vrednosti x_vrednost i y_vrednost tako da budu u opsegu od 0-128 odnosno 0-64
    //skaliranje x-koordinate

    X = (x_vrednost-161) * 0.03629;



//X= ((x_vrednost-AD_Xmin)/(AD_Xmax-AD_Xmin))*128;	
//vrednosti AD_Xmin i AD_Xmax su minimalne i maksimalne vrednosti koje daje AD konvertor za touch panel.


//Skaliranje Y-koordinate
	Y = (y_vrednost-500) * 0.020725;

//	Y= ((y_vrednost-AD_Ymin)/(AD_Ymax-AD_Ymin))*64;
}

void Write_GLCD(unsigned int data)
{
    unsigned char temp;

    temp=data/1000;
    Glcd_PutChar(temp+'0');
    data=data-temp*1000;
    temp=data/100;
    Glcd_PutChar(temp+'0');
    data=data-temp*100;
    temp=data/10;
    Glcd_PutChar(temp+'0');
    data=data-temp*10;
    Glcd_PutChar(data+'0');
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
    RS232_putst("PIR: ");
    WriteUART1dec2string(pir);
	for(broj2=0;broj2<1000;broj2++);
}

void ispisiMq3(unsigned int mq3) // ispisuje na terminal vrednost AD konverzije sa MQ3
{
    RS232_putst("MQ3: ");
	WriteUART1dec2string(mq3);
    for(broj2=0;broj2<1000;broj2++);
}

void ispisiFoto(unsigned int foto) // ispisuje na terminal vrednost AD konverzije sa fotootoprnika
{
    RS232_putst("FOTO: ");
    WriteUART1dec2string(foto);
	for(broj2=0;broj2<1000;broj2++);
}

unsigned int detektujPrilaz(unsigned int pir)
{
    if(pir > 2000) // PIR na jedinici daje oko 2500-3000 na AD konverziji
        {
            Delay_ms(7000); // sacekati da se smiri odziv PIR-a
            enpir++;
            if(enpir % 2 == 1)
                enfoto = 1; // enable za obasjavanje fotootpornika
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

void __attribute__ ((__interrupt__, no_auto_psv)) _T3Interrupt(void) // svakih 1ms
{
	TMR3 = 0;
    ms3 = 1; //fleg za milisekundu ili prekid ; potrebno ga je samo resetovati u funkciji

	brojac_ms3++; //brojac milisekundi
    stoperica3++; //brojac za funkciju Delay_ms3

    if (brojac_ms3 == 1000) //sek
        {
            brojac_ms3 = 0;
            sekund3 = 1; //fleg za sekundu
		} 
    
	IFS0bits.T3IF = 0;    
}

void servo0() // salje servo na 0 stepeni
{
    servo = 1;
    Delay_ms(5);
    servo = 0;
    Delay_ms(195);    
}
           
void servo90() // salje servo na 90 stepeni
{
    servo = 1;
    Delay_ms(15);
    servo = 0;
    Delay_ms(185);
}

void servo180() // salje servo na 180 stepeni
{
    servo = 1;
    Delay_ms(38);
    servo = 0;
    Delay_ms(162);
}

/*******************/
/*******************/

void Taster5()
{
    if (17 < X  &&  X < 44  &&  47 < Y  &&  Y < 55)
        korak = pocetna/10; // korak pwm=5%
}

void Taster10()
{
    if (17 < X  &&  X < 44  &&  15 < Y && Y<25)   
        korak = pocetna/5; // korak pwm=10%                     
}

void Strelica_gore()
{
	if (78 < X  &&  X < 100  &&  39 < Y  &&  Y < 56 )
 {
        if(vreme_on+korak<pocetna*2)
            vreme_on=vreme_on+korak;
        else 
            vreme_on=pocetna*2;
 }
}

void Strelica_dole()
{
  if (78 < X && X < 100 && 15 < Y && Y < 30)   //((88<X)&&(X<100)&& (15<Y)&&(Y<30)) => stare koordinate
	{                                     //(90<X)&&(X<120)&& (20<Y)&&(Y<40) => nove koordinate
       if(vreme_on - korak > 0)
            vreme_on = vreme_on - korak;
       else
            vreme_on = 0;
	}
}

void Set_pwm()
{
    if(vreme_on == pocetna * 2 + pocetna * 2 / 5)
    {
       LATFbits.LATF6 = 1;
       LATAbits.LATA11 = 1;
       vreme_off = 0;
    }
    else
    {
        vreme_off = pocetna * 2 - vreme_on;

        LATFbits.LATF6 = 1;
        LATAbits.LATA11 = 1;
        Delay_ms3(vreme_on);
        
        if(vreme_on != pocetna*2)
        {    
            LATFbits.LATF6 = 0;
            LATAbits.LATA11 = 0;
            Delay_ms3(vreme_off);
        }
    }    
}
/*
 * 
 */


int main(int argc, char** argv) {
        
        for(broj=0;broj<60000;broj++);
             
        TRISAbits.TRISA11 = 0; //izlazni pin
        TRISDbits.TRISD8 = 0; //izlazni pin
		
        for(broj=0;broj<60000;broj++); 

        
        ConfigureADCPins(); //podesi pinove za AD konverziju
        ConfigureLCDPins(); //podesi pinove za LCD
        ConfigureTSPins(); //podesi pinove za TouchScreen
        GLCD_LcdInit(); //inicijalizuj GLCD
        GLCD_ClrScr(); //obrisi GLCD
		initUART1(); //inicijalizacija UART-a
 		ADCinit(); //inicijalizacija AD konvertora
        
        
		ADCON1bits.ADON=1;//pocetak Ad konverzije 
        
        Init_T2();
        Init_T3();
        
	while(1)
	{ 
        if(rec[0] == 'D' && rec[1] == 'O'&& rec[2] == 'R' && rec[3] == 'O' && rec[4] == 'S')
        {
            rec[0] = 'A'; //rec[0]='A' zato sto inace non stop menja stanja, te je taster = 1 te je 0;
            taster++;
            if(taster % 2 == 0) 
                taster = 0;
        }
        
       
        
        if(taster == 1) //ukoliko je taster pritisnut menjamo stanje diode
        {
            Touch_Panel();
            GLCD_DisplayPicture(tasteri_bmp);
    
                /*GoToXY(0,6);
                GLCD_Printf ("X=");
                GoToXY(9,6);
                Write_GLCD(X);
        
                GoToXY(0,7);
                GLCD_Printf ("Y=");
                GoToXY(9,7);
                Write_GLCD(Y);*/
                
                
                Taster5();
                Taster10();
                Strelica_gore();
                Strelica_dole();
        
                Set_pwm();
                WriteUART1dec2string(vreme_off);
                WriteUART1(32);
                WriteUART1dec2string(vreme_on);
                WriteUART1(32);
                WriteUART1dec2string(korak);
                WriteUART1(13);
            }
        
        if(taster == 0)
        {
            if(zakljucan == 0)
            {
                enpir = 0;
                for(broj1 = 0; broj1 < 30; broj1++)
                    servo0(); //automobil zakljucan - inicijalno stanje
                zakljucan++; //da promenljiva zakljucan vise nije 0
                RS232_putst("ZAKLJUCAN");
            }
            
            
            if(detektujPrilaz(pir))
            {
                for(broj1 = 0; broj1 < 2; broj1++) //ovde se saceka da se odziv PIR senzora vrati na 0
                    Delay_ms(4000);
                enfoto = 1;
                RS232_putst("PIR DETEKTOVAO");
            }
                
            if(enfoto == 1 && foto < 200)
            {
                for(broj1 = 0; broj1 < 30; broj1++)
                    servo90(); // automobil otkljucan
                
                enfoto = 0; //spustamo flag
                enmq3 = 1; //dizemo flag i dozvoljavamo naredno stanje
                RS232_putst("OBASJAN SAM");
            }
            
            if(enmq3 == 1 )
            {
                for(broj1 = 0; broj1 < 15; broj1++) // sacekaj da se vrednost AD konverzije sa MQ3 poveca usled eventualnog prisustva alkohola
                    Delay_ms(7000);  /////////////////
                if(mq3 < 1000) //nema alkohola
                {
                    for(broj1 = 0; broj1 < 30; broj1++)
                        servo180(); // automobil dozvoljava paljenje
                    RS232_putst("SRECAN PUT");
                    zakljucan = 0;
                }
                else //ima alkohola
                {
                    RS232_putst("Ej druze pijan si");
                    zakljucan = 0;
                }
                enmq3 = 0;
            }
            
            WriteUART1dec2string(enpir);
        
           
            
        /*ispisiPir(pir);
        ispisiMq3(mq3);
        ispisiFoto(foto);
       
        //WriteUART(vreme2)*/
		WriteUART1(13);//enter
        Delay_ms(2000);
        }
	}//od whilea

    return (EXIT_SUCCESS);
}