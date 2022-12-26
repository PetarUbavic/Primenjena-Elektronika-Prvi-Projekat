#include <p30fxxxx.h>
#include <outcompare.h>
#include "timer2.h"
_FOSC(CSW_FSCM_OFF & XT_PLL4);//instruction takt je isti kao i kristal
_FWDT(WDT_OFF);


unsigned int broj1,broj2,r;


void __attribute__((__interrupt__)) _T2Interrupt(void)
{

   	TMR2 =0;
    IFS0bits.T2IF = 0;
}


int main(void)
	{
        for(broj1=0;broj1<10000;broj1++);



        TRISDbits.TRISD0=0;//konfigurisemo kao izlaz za pwm




        PR2=2499;//odredjuje frekvenciju po formuli
        OC1RS=20;//postavimo pwm
        OC1R=1000;//inicijalni pwm pri paljenju samo
        OC1CON = OC_IDLE_CON & OC_TIMER2_SRC & OC_PWM_FAULT_PIN_DISABLE& T2_PS_1_256;//konfiguracija pwma
        T2CONbits.TON=1;//ukljucujemo timer koji koristi


        r=2500;
        OC1RS=r;//ovim postavljamo faktor ispune


        for(broj1=0;broj1<700;broj1++)
        for(broj2=0;broj2<3000;broj2++);

	while(1)
	{
        if(r<2499)
            {
                r++;
                OC1RS=r;//ovim postavljamo pwm
            }
        else
            {

                r=0;
                OC1RS=r;

            }


            for(broj1=0;broj1<20;broj1++)
                for(broj2=0;broj2<60;broj2++);







}//od whilea
return 0;
}//od maina


//za 100% mora se staviti OC1RS>PR2 ili koji je vec izabran

//za 0% dovoljno je staviti OC1RS na 0 
//rezolucija pwma zavisi od izabrane periode


