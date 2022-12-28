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
const unsigned int AD_Xmin =220;
const unsigned int AD_Xmax =3642;
const unsigned int AD_Ymin =520;
const unsigned int AD_Ymax =3450;

unsigned int sirovi0,sirovi1;
unsigned int broj,broj1,broj2,temp0,temp1;

//#define DRIVE_A PORTBbits.RB10
//#define DRIVE_B PORTCbits.RC13
#define DRIVE_A PORTCbits.RC13
#define DRIVE_B PORTCbits.RC14

#define servo LATDbits.LATD8

unsigned int X, Y,x_vrednost, y_vrednost;

unsigned int pir,mq3,foto, enpir, enfoto;
unsigned int broj,broj1,broj2,tempRX;

unsigned int brojac_ms,stoperica,ms,sekund;
unsigned int brojac_ms3,stoperica3,ms3,sekund3;

unsigned int korak=20;
unsigned int vreme = 100;
unsigned int vreme2=100;
unsigned int morzeI=0;
unsigned int morzeBrojac=0;
unsigned int x;
unsigned int niz[3];
unsigned char sifra[3];
unsigned char sifraProvera;
char r=1;
bool y;

/***************************************************************************
* Ime funkcije      : initUART1                                            *
* Opis              : inicjalizuje RS232 komunikaciju s 9600bauda          * 
* Parameteri        : Nema                                                 *
* Povratna vrednost : Nema                                                 *
***************************************************************************/

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
  //   tempRX=U1RXREG;
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

/*********************************************************************
* Ime funkcije      : WriteUART1                            		 *
* Opis              : Funkcija upisuje podatke u registar U1TXREG,   *
*                     za slanje podataka    						 *
* Parameteri        : unsigned int data-podatak koji zelimo poslati  *
* Povratna vrednost : Nema                                           *
*********************************************************************/

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

	Delay_ms(50); //cekamo jedno vreme da se odradi AD konverzija
	
	// ocitavamo y	
	y_vrednost = temp1;// temp1 je vrednost koji nam daje AD konvertor na LEFT pinu	
	
//Ako ?elimo da nam X i Y koordinate budu kao rezolucija ekrana 128x64 treba skalirati vrednosti x_vrednost i y_vrednost tako da budu u opsegu od 0-128 odnosno 0-64
//skaliranje x-koordinate

    X=(x_vrednost-161)*0.03629;



//X= ((x_vrednost-AD_Xmin)/(AD_Xmax-AD_Xmin))*128;	
//vrednosti AD_Xmin i AD_Xmax su minimalne i maksimalne vrednosti koje daje AD konvertor za touch panel.


//Skaliranje Y-koordinate
	Y= ((y_vrednost-500)*0.020725);

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

void __attribute__ ((__interrupt__, no_auto_psv)) _T3Interrupt(void) // svakih 1ms
{
	TMR3 =0;
     ms3=1;//fleg za milisekundu ili prekid;potrebno ga je samo resetovati u funkciji

	brojac_ms3++;//brojac milisekundi
    stoperica3++;//brojac za funkciju Delay_ms

    if (brojac_ms3==1000)//sek
        {
          brojac_ms3=0;
          sekund3=1;//fleg za sekundu
		 } 
	IFS0bits.T3IF = 0;    
}



void servo0()
{
    servo = 1;
    Delay_ms(5);
    servo = 0;
    Delay_ms(195);
    
    /*PR2=65500;
    OC1RS = 7; //ovim postavljamo faktor ispune
*/
     }

void servo90()
{
    servo = 1;
    Delay_ms(15);
    servo = 0;
    Delay_ms(185); 
    
   /* PR2=65500;
    OC1RS = 25; //ovim postavljamo faktor ispune*/
}

void servo180()
{
    servo = 1;
    Delay_ms(38);
    servo = 0;
    Delay_ms(162);
    
    /*PR2=65500;//odredjuje frekvenciju po formuli
    OC1RS = 50;    //ovim postavljamo faktor ispune*/
    
}


bool proveriSifru()
{
    if(sifra[0] == '-' && sifra[1] == '.' && sifra[2] == '-') //morzeov kod za slovo K je -.-
        return 1;
    else
        return 0;
}


bool morze()
{
  lstart:  if(foto > 1000) // mozda treba while / do while
    {
        Delay_ms(100); //sacekaj 10ms
        morzeI++; //povecaj morzeI (neki brojac), ako je npr morzeI = 10, to znaci da je svetlosni impuls trajao 100ms
        x = morzeI; //upisi vrednost brojaca u promenljivu x
        WriteUART1('T'); //debuguing linija
    }
    else
    {
        morzeI=0; //doslo je do prekida svetlosti, stavi brojac na 0
        x = x*10; //mnozim sa 10 da bi dobio x u mili sekundama
        WriteUART1('N'); // debuging linija
        //WriteUART1dec2string(x); //debuging linija
        
        ////////////////////////
        if(morzeBrojac < 3 && x != 0)  // ovaj deo ne radi, treba se jos igrati da vidimo sta je
        {
            niz[morzeBrojac]=x;
            x=0;
            morzeBrojac++;
        }
        else if(morzeBrojac == 2)
        {
            if(niz[0] > 800   &&   niz[0] < 1200)
                sifra[0]  = '-';
            else if(niz[0] > 350  &&  niz[0] < 650)
                sifra[0] = '.';

            if(niz[1] > 800   &&   niz[1] < 1200)
                sifra[1]  = '-';
            else if(niz[1] > 350  &&  niz[1] < 650)
                sifra[1] = '.';

            if(niz[2] > 800   &&   niz[2] < 1200)
                sifra[2]  = '-';
            else if(niz[2] > 350  &&  niz[2] < 650)
                sifra[2] = '.';

            if(proveriSifru() == 1)
                return 1;
            else if(proveriSifru() == 0)
                return 0;

            morzeBrojac = 0;     
        }
        ////////////////////////
    } 
    
    goto lstart;
}


/*
 * 
 */
void Taster5()
{
    if ((17<X)&&(X<44)&& (47<Y)&&(Y<55))
        { 
        korak=10;
        //vreme=10;
            /*LATBbits.LATB5=1;
            Delay_ms(vreme);
    	    LATBbits.LATB5=0;
    	    perioda=perioda-vreme;
            Delay_ms(perioda);*/
    
        }// korak pwm=5%
}

void Taster10()
{
    if ((17<X)&&(X<44)&& (15<Y)&&(Y<25))
    { korak=20;
            //vreme=20;
      /*LATBbits.LATB5=1;
      Delay_ms(vreme);
      LATBbits.LATB5=0;
      perioda=perioda-vreme;
      Delay_ms(perioda);*/
     //perioda 20ms
      }
        // korak pwm=10%
}


void Strelica_gore()
{
	if ((88<X)&&(X<100)&& (47<=Y)&&(Y<=55))
 { 
     vreme=vreme+korak;
 }
}


void Strelica_dole()
{
  if ((88<X)&&(X<100)&& (15<Y)&&(Y<30))
	{
	   vreme=vreme-korak;
	}
}

void Set_pwm()
{
    vreme2=200-vreme;
    LATFbits.LATF6=0;
    Delay_ms3(vreme2);
    LATFbits.LATF6=1;
    
    Delay_ms3(vreme);
    
    
}


int main(int argc, char** argv) {
        
        for(broj=0;broj<60000;broj++);
             
        TRISDbits.TRISD8=0; //izlazni pin
		
        for(broj=0;broj<60000;broj++);

        
        ConfigureADCPins();
        ConfigureLCDPins();
        ConfigureTSPins();
        GLCD_LcdInit();
        GLCD_ClrScr();
		initUART1();//inicijalizacija UART-a
 		ADCinit();//inicijalizacija AD konvertora
        
        
        
        
        
		ADCON1bits.ADON=1;//pocetak Ad konverzije 
        
        Init_T2();
        Init_T3();
	while(1)
	{       
        Touch_Panel();
        GLCD_DisplayPicture(tasteri_bmp);
        
        GoToXY(0,6);
        GLCD_Printf ("X=");
        GoToXY(9,6);
        Write_GLCD(X);
	        
		GoToXY(0,7);
        GLCD_Printf ("Y=");
        GoToXY(9,7);
        Write_GLCD(Y);
        
        
         /*if ((59<X)&&(X<111)&& (6<Y)&&(Y<15))
            {  
             
          	  GLCD_ClrScr();
            }*/
        
        
       /* switch(r)
        {
            case 1:
                for(broj1=0; broj1<100; broj1++)
                    servo0();
               if(enfoto==1)
                   r++;
            case 2:
               if(morze() == 1)
               {
                   servo90();
                   r++;
               }
                for(broj1=0; broj1<100; broj1++)
                    servo90();
                r++;
            case 3:
                if(mq3 < 1100)
                {
                    servo180();
                    r=0;
                }
            default: break;
        };*/
        
        
                
           
        Taster10();        
        Taster5();
        Strelica_gore();
        Strelica_dole();
        
        Set_pwm();
        
        //servo0();
        /*ispisiPir(pir);
        ispisiMq3(mq3);
        ispisiFoto(foto);*/
       //  y = morze();
       // if(y==1)
       //     WriteUART1('P');
       // else if(y==0)
       //     WriteUART1('K');
        //WriteUART1(sifra[0]);
        //WriteUART1(sifra[1]);
        //WriteUART1(sifra[2]);
        //WriteUART(vreme2)
		//WriteUART1(13);//enter
                
       // servo0();
        //Delay_ms(2000);
	}//od whilea

    return (EXIT_SUCCESS);
}