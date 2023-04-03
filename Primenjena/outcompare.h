/********************************************************************/
//              Header for OutCompare module library functions      */
/********************************************************************/

#if defined(__dsPIC30F__)
#include <p30Fxxxx.h>
#elif defined(__dsPIC33F__)
#include <p33Fxxxx.h>
#elif defined(__PIC24H__)
#include <p24Hxxxx.h>
#elif defined(__dsPIC33E__)
#include <p33Exxxx.h>
#elif defined(__PIC24E__)
#include <p24Exxxx.h>
#else
//#error "Does not build on this target"
#endif


#ifndef __OutCompare_H
#define __OutCompare_H

/* List of SFRs for Output compare modules */

#define OC1RS_VALUE                0x0000
#define OC1R_VALUE                 0x0000
#define OC1CON_VALUE               0x0000

#ifdef _OC2IF

#define OC2RS_VALUE                0x0000
#define OC2R_VALUE                 0x0000
#define OC2CON_VALUE               0x0000

#endif

#ifdef _OC3IF

#define OC3RS_VALUE                0x0000
#define OC3R_VALUE                 0x0000
#define OC3CON_VALUE               0x0000

#endif

#ifdef _OC4IF

#define OC4RS_VALUE                0x0000
#define OC4R_VALUE                 0x0000
#define OC4CON_VALUE               0x0000

#endif

#ifdef _OC5IF

#define OC5RS_VALUE                0x0000
#define OC5R_VALUE                 0x0000
#define OC5CON_VALUE               0x0000

#endif

#ifdef _OC6IF

#define OC6RS_VALUE                0x0000
#define OC6R_VALUE                 0x0000
#define OC6CON_VALUE               0x0000

#endif

#ifdef _OC7IF

#define OC7RS_VALUE                0x0000
#define OC7R_VALUE                 0x0000
#define OC7CON_VALUE               0x0000

#endif

#ifdef _OC8IF

#define OC8RS_VALUE                0x0000
#define OC8R_VALUE                 0x0000
#define OC8CON_VALUE               0x0000

#endif

#if defined(__dsPIC33E__) || defined(__PIC24E__)  

#ifdef _OC1IF
#define OC1RS_VALUE                0x0000
#define OC1R_VALUE                 0x0000
#define OC1CON1_VALUE              0x0000
#define OC1CON2_VALUE              0x0000
#endif

#ifdef _OC2IF
#define OC2RS_VALUE                0x0000
#define OC2R_VALUE                 0x0000
#define OC2CON1_VALUE              0x0000
#define OC2CON2_VALUE              0x0000
#endif

#ifdef _OC3IF
#define OC3RS_VALUE                0x0000
#define OC3R_VALUE                 0x0000
#define OC3CON1_VALUE              0x0000
#define OC3CON2_VALUE              0x0000
#endif

#ifdef _OC4IF
#define OC4RS_VALUE                0x0000
#define OC4R_VALUE                 0x0000
#define OC4CON1_VALUE              0x0000
#define OC4CON2_VALUE              0x0000
#endif

#ifdef _OC5IF
#define OC5RS_VALUE                0x0000
#define OC5R_VALUE                 0x0000
#define OC5CON1_VALUE              0x0000
#define OC5CON2_VALUE              0x0000
#endif

#ifdef _OC6IF
#define OC6RS_VALUE                0x0000
#define OC6R_VALUE                 0x0000
#define OC6CON1_VALUE              0x0000
#define OC6CON2_VALUE              0x0000
#endif

#ifdef _OC7IF
#define OC7RS_VALUE                0x0000
#define OC7R_VALUE                 0x0000
#define OC7CON1_VALUE              0x0000
#define OC7CON2_VALUE              0x0000
#endif

#ifdef _OC8IF
#define OC8RS_VALUE                0x0000
#define OC8R_VALUE                 0x0000
#define OC8CON1_VALUE              0x0000
#define OC8CON2_VALUE              0x0000
#endif

#ifdef _OC9IF
#define OC9RS_VALUE                0x0000
#define OC9R_VALUE                 0x0000
#define OC9CON1_VALUE              0x0000
#define OC9CON2_VALUE              0x0000
#endif

#ifdef _OC10IF
#define OC10RS_VALUE                0x0000
#define OC10R_VALUE                 0x0000
#define OC10CON1_VALUE              0x0000
#define OC10CON2_VALUE              0x0000
#endif

#ifdef _OC1IF
#define OC11RS_VALUE                0x0000
#define OC11R_VALUE                 0x0000
#define OC11CON1_VALUE              0x0000
#define OC11CON2_VALUE              0x0000
#endif

#ifdef _OC12IF
#define OC12RS_VALUE                0x0000
#define OC12R_VALUE                 0x0000
#define OC12CON1_VALUE              0x0000
#define OC12CON2_VALUE              0x0000
#endif

#ifdef _OC13IF
#define OC13RS_VALUE                0x0000
#define OC13R_VALUE                 0x0000
#define OC13CON1_VALUE              0x0000
#define OC13CON2_VALUE              0x0000
#endif

#ifdef _OC14IF
#define OC14RS_VALUE                0x0000
#define OC14R_VALUE                 0x0000
#define OC14CON1_VALUE              0x0000
#define OC14CON2_VALUE              0x0000
#endif

#ifdef _OC15IF
#define OC15RS_VALUE                0x0000
#define OC15R_VALUE                 0x0000
#define OC15CON1_VALUE              0x0000
#define OC15CON2_VALUE              0x0000
#endif

#ifdef _OC16IF
#define OC16RS_VALUE                0x0000
#define OC16R_VALUE                 0x0000
#define OC16CON1_VALUE              0x0000
#define OC16CON2_VALUE              0x0000
#endif

#endif

#if defined(__dsPIC33E__) || defined(__PIC24E__) 

#define OC_IDLE_STOP               	0xffff /* stop in idle mode */
#define OC_IDLE_CON                	0xdfff /* continue operation in idle mode */

/* Section : Output Compare timer select Bit Defines */
#define OC_SYSCLK_SRC               0xffff  /*System Clock is the clock source for OutputCompare*/
#define OC_PTGO_SRC               	0xf7ff  /* PTGO is the clock source for OutputCompare */
#define OC_TIMER1_SRC               0xf3ff  /* Timer1 is the clock source for OutputCompare */
#define OC_TIMER5_SRC               0xefff  /* Timer5 is the clock source for OutputCompare */
#define OC_TIMER4_SRC               0xebff  /* Timer4 is the clock source for OutputCompare */
#define OC_TIMER3_SRC               0xe7ff  /* Timer3 is the clock source for OutputCompare */
#define OC_TIMER2_SRC               0xe3ff  /* Timer2 is the clock source for OutputCompare */

/*Section : Fault A Input Enable/Disable */
#define OC_FAULTA_IN_ENABLE      0xfcff /*PWM Fault A Input Enabled*/
#define OC_FAULTA_IN_DISABLE   	0xfc7f /*PWM Fault A Input Disabled*/

/*Section : Fault B Input Enable/Disable */
#define OC_FAULTB_IN_ENABLE      0xfd7f /*PWM Fault B Input Enabled*/
#define OC_FAULTB_IN_DISABLE   	0xfc7f /*PWM Fault B Input Disabled*/

/*Section : Fault C Input Enable/Disable */
#define OC_FAULTC_IN_ENABLE      0xfe7f /*PWM Fault C Input Enabled*/
#define OC_FAULTC_IN_DISABLE   	0xfc7f /*PWM Fault C Input Disabled*/

/*Section : PWM Fault Condition Status*/
#define OC_PWM_FAULT_CLEAR          0xffef /*Fault status bit will be cleared in software*/

/*Section : One Shot Enable/Disable*/
#define OC_TRIG_CLEAR_SYNC          0xffff /*Trigger is cleared synchronously(OCxRs=TIMER) or by software*/
#define OC_TRIG_CLEAR_SW            0xfff7 /*Trigger cleared by software*/

/*Section : OutputCompare Mode Select */
#define OC_PWM_CENTRE_ALIGN         0xffff  /* Center Aligned PWM Mode on OCx pin */
#define OC_PWM_EDGE_ALIGN           0xfffe  /* Edge Aligned PWM Mode on OCx pin */
#define OC_CONTINUE_PULSE           0xfffd  /* Generates Continuous Output pulse on OCx Pin */
#define OC_SINGLE_PULSE             0xfffc  /* Generates Single Output pulse on OCx Pin */
#define OC_TOGGLE_PULSE             0xfffb  /* Compare1 toggles  OCx pin*/
#define OC_HIGH_LOW                 0xfffa  /* Compare1 forces   OCx pin Low*/
#define OC_LOW_HIGH                 0xfff9  /* Compare1 forces  OCx pin High*/
#define OC_OFF                      0xfff8  /* OutputCompare x Off*/

/*Section : Fault Mode Bit*/
#define OC_FAULT_MODE_CLEAR_SW      0xffff /*Fault condition maintained until OCxFLT is cleared*/
#define OC_FAULT_MODE_PWM_CYCLE     0x7fff /*Fault condition maintained until new PWM cycle starts*/

/*Section : Fault Out Bit*/
#define OC_PWM_FAULT_OUT_HIGH       0xffff /*Outputcompare output is driven high during fault condition*/
#define OC_PWM_FAULT_OUT_LOW        0xbfff /*Outputcompare output is driven low during fualt condition*/

/* Section : Fault Output state select bit*/
#define OC_FAULT_PIN_OUT            0x2000 /*oc_oe_out is low during fault condition*/
#define OC_FAULT_PIN_UNCHANGE       0x0000 /*oc_oe_out is unchanged during fault condition*/
#define OC_FAULT_TRISTATE_MASK       (~OC_FAULT_OE_OUT_LOW)

/*Section : Ouput Compare Invert Bit*/
#define OC_OUT_INVERT               0xffff /*OutputCompare output is inverted*/
#define OC_OUT_NOT_INVERT           0xefff /*OutputCompare output is not inverted*/

/*Section : Output Compare Cascade Module Operation*/
#define OC_CASCADE_ENABLE           0xffff /*Output Compare Cascade Module Enabled*/
#define OC_CASCADE_DISABLE          0xfeff /*Output Compare Cascade Module Disabled*/

/*Section : Output Compare Trigger Operation Select*/
#define OC_TRIGGER_ENABLE           0xffff /*sync_trig[x] used to trigger the module timer*/
#define OC_SYNC_ENABLE			    0xf7ff /* Sync_trig[x] is used to sync to another module timer */

/*Section : Output Compare Timer Trigger*/
#define OC_TRIGGER_TIMER 		    0xffff	/* Timer has been triggered and is running */
#define OC_UNTRIGGER_TIMER		    0xffbf  /* Timer not triigered and is being held in clear */

/*Section : Output Compare x Off bit*/
#define OC_DIRN_TRIS              0xffff  /*The signal ocmp_oe_out is forced to zero*/
#define OC_DIRN_OUTPUT         0xffdf  /*The signal ocmp_oe_out can be active*/

/*Section : Source Select for Synchronization and Trigger Operation*/
#define OC_SYNC_TRIG_IN_DISABLE 	0xffe0	/* Disables trigger operation */
#define OC_SYNC_TRIG_IN_OC1		0xffe1	/* Sync or Trigger input is OC1 */
#define OC_SYNC_TRIG_IN_OC2		0xffe2	/* Sync or Trigger input is OC2 */
#define OC_SYNC_TRIG_IN_OC3		0xffe3	/* Sync or Trigger input is OC3 */
#define OC_SYNC_TRIG_IN_OC4		0xffe4	/* Sync or Trigger input is OC4 */
#define OC_SYNC_TRIG_IN_OC5		0xffe5	/* Sync or Trigger input is OC5 */
#define OC_SYNC_TRIG_IN_OC6		0xffe6	/* Sync or Trigger input is OC6 */
#define OC_SYNC_TRIG_IN_OC7		0xffe7	/* Sync or Trigger input is OC7 */
#define OC_SYNC_TRIG_IN_OC8		0xffe8	/* Sync or Trigger input is OC8 */
#define OC_SYNC_TRIG_IN_OC9		0xffe9	/* Sync or Trigger input is OC9 */
#define OC_SYNC_TRIG_IN_PTGO		0xffea	/* Sync or Trigger input is PTGOx */
#define OC_SYNC_TRIG_IN_TMR1		0xffeb	/* Sync or Trigger input is Timer1 */
#define OC_SYNC_TRIG_IN_TMR2		0xffec	/* Sync or Trigger input is Timer2 */
#define OC_SYNC_TRIG_IN_TMR3		0xffed	/* Sync or Trigger input is Timer3 */
#define OC_SYNC_TRIG_IN_TMR4		0xffee	/* Sync or Trigger input is Timer4 */
#define OC_SYNC_TRIG_IN_TMR5		0xffef	/* Sync or Trigger input is Timer5 */
#define OC_SYNC_TRIG_IN_IC1		0xfff0	/* Sync or Trigger input is ICAP1 */
#define OC_SYNC_TRIG_IN_IC2		0xfff1	/* Sync or Trigger input is ICAP2 */
#define OC_SYNC_TRIG_IN_IC3		0xfff2	/* Sync or Trigger input is ICAP3 */
#define OC_SYNC_TRIG_IN_IC4		0xfff3	/* Sync or Trigger input is ICAP4 */
#define OC_SYNC_TRIG_IN_IC5		0xfff4	/* Sync or Trigger input is ICAP5 */
#define OC_SYNC_TRIG_IN_IC6		0xfff5	/* Sync or Trigger input is ICAP6 */
#define OC_SYNC_TRIG_IN_IC7		0xfff6	/* Sync or Trigger input is ICAP7 */
#define OC_SYNC_TRIG_IN_IC8		0xfff7	/* Sync or Trigger input is ICAP8 */
#define OC_SYNC_TRIG_IN_CMP1		0xfff8	/* Sync or Trigger input is CMP1 */
#define OC_SYNC_TRIG_IN_CMP2		0xfff9	/* Sync or Trigger input is CMP2 */
#define OC_SYNC_TRIG_IN_CMP3		0xfffa	/* Sync or Trigger input is CMP3 */
#define OC_SYNC_TRIG_IN_AD		0xfffb	/* Sync or Trigger input is AD */
#define OC_SYNC_TRIG_IN_CTMU		0xfffc	/* Sync or Trigger input is CTMU */
#define OC_SYNC_TRIG_IN_INT1		0xfffd	/* Sync or Trigger input is INT1 */
#define OC_SYNC_TRIG_IN_INT2		0xfffe	/* Sync or Trigger input is INT2 */

#else

/* Output Compare Stop in Idle mode Bit defines */
#define OC_IDLE_STOP               0xffff   /* stop in idle mode */
#define OC_IDLE_CON                0xdfff   /* continue operation in idle mode */

/* Output Compare timer select Bit Defines */
#define OC_TIMER2_SRC               0xfff7  /* Timer2 is the clock source 
                                                    for OutputCompare1 */
#define OC_TIMER3_SRC               0xffff  /* Timer3 is the clock source
                                                     for OutputCompare1 */

/* PWM Mode on OCx, fault pin enabled, (TxIF bit is set for PWM, OCxIF is set for fault)*/
#define OC_PWM_FAULT_PIN_ENABLE     0xffff

/* PWM Mode on OCx, fault pin disabled */
#define OC_PWM_FAULT_PIN_DISABLE    0xfffe
   
/* Generates Continuous Output pulse on OCx Pin */
#define OC_CONTINUE_PULSE           0xfffd
  
/* Generates Single Output pulse on OCx Pin */
#define OC_SINGLE_PULSE             0xfffc  
#define OC_TOGGLE_PULSE             0xfffb  /* Compare1 toggels  OCx pin*/
#define OC_HIGH_LOW                 0xfffa  /* Compare1 forces   OCx pin Low*/
#define OC_LOW_HIGH                 0xfff9  /* Compare1 forces  OCx pin High*/
#define OC_OFF                      0xfff8  /* OutputCompare x Off*/

#endif

/* Interrupt bit definitions */
#define OC_INT_ON                   0xffff  /* OutputCompare Enable  */
#define OC_INT_OFF                  0xfff7  /* OutputCompare Disable */
    
#define OC_INT_PRIOR_0              0xfff8  /* OutputCompare PriorityLevel 0 */
#define OC_INT_PRIOR_1              0xfff9  /* OutputCompare PriorityLevel 1 */
#define OC_INT_PRIOR_2              0xfffa  /* OutputCompare PriorityLevel 2 */
#define OC_INT_PRIOR_3              0xfffb  /* OutputCompare PriorityLevel 3 */
#define OC_INT_PRIOR_4              0xfffc  /* OutputCompare PriorityLevel 4 */
#define OC_INT_PRIOR_5              0xfffd  /* OutputCompare PriorityLevel 5 */
#define OC_INT_PRIOR_6              0xfffe  /* OutputCompare PriorityLevel 6 */
#define OC_INT_PRIOR_7              0xffff  /* OutputCompare PriorityLevel 7 */


#define Start                       0x01
#define Stop                        0x00

#define EnableIntOC1                    _OC1IE = 1
#define DisableIntOC1                   _OC1IE = 0
#define SetPriorityIntOC1(priority)     _OC1IP = priority

/*  CloseOC1    */
void CloseOC1() __attribute__((section (".libperi")));

/* ConfigIntOC1  */
void ConfigIntOC1(unsigned int config) __attribute__ ((section (".libperi")));

/*  OpenOC1   */
#if defined(__dsPIC33E__) || defined(__PIC24E__) 
void OpenOC1(unsigned int config1,unsigned int config2,unsigned int value1,
                 unsigned int value2) __attribute__ ((section (".libperi")));
#else
void OpenOC1(unsigned int config,unsigned int value1,
                 unsigned int value2) __attribute__ ((section (".libperi")));
#endif

/*  ReadDCOC1PWM    */
unsigned int ReadDCOC1PWM() __attribute__((section (".libperi")));

/*  ReadRegOC1    */
unsigned int ReadRegOC1(char reg) __attribute__((section (".libperi")));

/*  SetDCOC1PWM  */
#if defined(__dsPIC33E__) || defined(__PIC24E__) 
char SetDCOC1PWM(unsigned int dutycycle,unsigned int period) __attribute__((section (".libperi")));
#else
char SetDCOC1PWM(unsigned int dutycycle) __attribute__((section (".libperi")));
#endif

/*  SetPulseOC1    */
void SetPulseOC1(unsigned int pulse_start,unsigned int pulse_stop) __attribute__((section (".libperi")));

#ifdef _OC2IF

#define EnableIntOC2                    _OC2IE = 1
#define DisableIntOC2                   _OC2IE = 0
#define SetPriorityIntOC2(priority)     _OC2IP = priority

/*  CloseOC2    */
void CloseOC2() __attribute__((section (".libperi")));

/* ConfigIntOC2  */
void ConfigIntOC2(unsigned int config) __attribute__ ((section (".libperi")));

/*  OpenOC2   */
#if defined(__dsPIC33E__) || defined(__PIC24E__) 
void OpenOC2(unsigned int config1,unsigned int config2,unsigned int value1,
                 unsigned int value2) __attribute__ ((section (".libperi")));
#else
void OpenOC2(unsigned int config,unsigned int value1,
                 unsigned int value2) __attribute__ ((section (".libperi")));
#endif

/*  ReadDCOC2PWM    */
unsigned int ReadDCOC2PWM() __attribute__((section (".libperi")));

/*  ReadRegOC2    */
unsigned int ReadRegOC2(char reg) __attribute__((section (".libperi")));

/*  SetDCOC2PWM  */
#if defined(__dsPIC33E__) || defined(__PIC24E__) 
char SetDCOC2PWM(unsigned int dutycycle,unsigned int period) __attribute__((section (".libperi")));
#else
char SetDCOC2PWM(unsigned int dutycycle) __attribute__((section (".libperi")));
#endif

/*  SetPulseOC2    */
void SetPulseOC2(unsigned int pulse_start,unsigned int pulse_stop) __attribute__((section (".libperi")));
    
#endif

#ifdef _OC3IF

#define EnableIntOC3                    _OC3IE = 1
#define DisableIntOC3                   _OC3IE = 0
#define SetPriorityIntOC3(priority)     _OC3IP = priority

/*  CloseOC3    */
void CloseOC3() __attribute__ ((section (".libperi")));

/* ConfigIntOC3  */
void ConfigIntOC3(unsigned int config) __attribute__((section(".libperi")));

/*  OpenOC3   */
#if defined(__dsPIC33E__) || defined(__PIC24E__) 
void OpenOC3(unsigned int config1,unsigned int config2,unsigned int value1,
                 unsigned int value2) __attribute__ ((section (".libperi")));
#else
void OpenOC3(unsigned int config,unsigned int value1,
                 unsigned int value2) __attribute__ ((section (".libperi")));
#endif

/*  ReadDCOC3    */
unsigned int ReadDCOC3PWM() __attribute__ ((section (".libperi")));

/*  ReadRegOC3    */
unsigned int ReadRegOC3(char reg) __attribute__ ((section(".libperi")));

/*  SetDCOC3PWM  */
#if defined(__dsPIC33E__) || defined(__PIC24E__) 
char SetDCOC3PWM(unsigned int dutycycle,unsigned int period) __attribute__((section (".libperi")));
#else
char SetDCOC3PWM(unsigned int dutycycle) __attribute__((section (".libperi")));
#endif

/*  SetPulseOC3    */
void SetPulseOC3(unsigned int pulse_start,unsigned int pulse_stop) __attribute__ 
((section (".libperi")));

#endif    

#ifdef _OC4IF

#define EnableIntOC4                    _OC4IE = 1
#define DisableIntOC4                   _OC4IE = 0
#define SetPriorityIntOC4(priority)     _OC4IP = priority

/*  CloseOC4    */
void CloseOC4() __attribute__ ((section (".libperi")));

/* ConfigIntOC4  */
void ConfigIntOC4(unsigned int config) __attribute__((section(".libperi")));

/*  OpenOC4   */
#if defined(__dsPIC33E__) || defined(__PIC24E__) 
void OpenOC4(unsigned int config1,unsigned int config2,unsigned int value1,
                 unsigned int value2) __attribute__ ((section (".libperi")));
#else
void OpenOC4(unsigned int config,unsigned int value1,
                 unsigned int value2) __attribute__ ((section (".libperi")));
#endif

/*  ReadDCOC4    */
unsigned int ReadDCOC4PWM() __attribute__ ((section (".libperi")));

/*  ReadRegOC4     */
unsigned int ReadRegOC4(char reg) __attribute__ ((section(".libperi")));

/*  SetDCOC4PWM  */
#if defined(__dsPIC33E__) || defined(__PIC24E__) 
char SetDCOC4PWM(unsigned int dutycycle,unsigned int period) __attribute__((section (".libperi")));
#else
char SetDCOC4PWM(unsigned int dutycycle) __attribute__((section (".libperi")));
#endif

/*  SetPulseOC4    */
void SetPulseOC4(unsigned int pulse_start,unsigned int pulse_stop) __attribute__ 
((section (".libperi")));

#endif

#ifdef _OC5IF

#define EnableIntOC5                    _OC5IE = 1
#define DisableIntOC5                   _OC5IE = 0
#define SetPriorityIntOC5(priority)     _OC5IP = priority

/*  CloseOC5    */
void CloseOC5() __attribute__ ((section (".libperi")));

/* ConfigIntOC5  */
void ConfigIntOC5(unsigned int config) __attribute__ ((section(".libperi")));

/*  OpenOC5   */
#if defined(__dsPIC33E__) || defined(__PIC24E__) 
void OpenOC5(unsigned int config1,unsigned int config2,unsigned int value1,
                 unsigned int value2) __attribute__ ((section (".libperi")));
#else
void OpenOC5(unsigned int config,unsigned int value1,
                 unsigned int value2) __attribute__ ((section (".libperi")));
#endif

/*  ReadDCOC5PWM    */
unsigned int ReadDCOC5PWM() __attribute__ ((section (".libperi")));

/*  ReadRegOC5    */
unsigned int ReadRegOC5(char reg) __attribute__ ((section(".libperi")));

/*  SetDCOC5PWM  */
#if defined(__dsPIC33E__) || defined(__PIC24E__) 
char SetDCOC5PWM(unsigned int dutycycle,unsigned int period) __attribute__((section (".libperi")));
#else
char SetDCOC5PWM(unsigned int dutycycle) __attribute__((section (".libperi")));
#endif

/*  SetPulseOC5    */
void SetPulseOC5(unsigned int pulse_start,unsigned int pulse_stop) __attribute__ 
((section (".libperi")));

#endif

#ifdef _OC6IF

#define EnableIntOC6                    _OC6IE = 1
#define DisableIntOC6                   _OC6IE = 0
#define SetPriorityIntOC6(priority)     _OC6IP = priority

/*  CloseOC6    */
void CloseOC6() __attribute__ ((section (".libperi")));

/* ConfigIntOC6  */
void ConfigIntOC6(unsigned int config) __attribute__ ((section(".libperi")));

/*  OpenOC6   */
#if defined(__dsPIC33E__) || defined(__PIC24E__) 
void OpenOC6(unsigned int config1,unsigned int config2,unsigned int value1,
                 unsigned int value2) __attribute__ ((section (".libperi")));
#else
void OpenOC6(unsigned int config,unsigned int value1,
                 unsigned int value2) __attribute__ ((section (".libperi")));
#endif

/*  ReadDCOC6PWM    */
unsigned int ReadDCOC6PWM() __attribute__ ((section (".libperi")));

/*  ReadRegOC6    */
unsigned int ReadRegOC6(char reg) __attribute__ ((section(".libperi")));

/*  SetDCOC6PWM  */
#if defined(__dsPIC33E__) || defined(__PIC24E__) 
char SetDCOC6PWM(unsigned int dutycycle,unsigned int period) __attribute__((section (".libperi")));
#else
char SetDCOC6PWM(unsigned int dutycycle) __attribute__((section (".libperi")));
#endif

/*  SetPulseOC6    */
void SetPulseOC6(unsigned int pulse_start,unsigned int pulse_stop) __attribute__ 
((section (".libperi")));

#endif

#ifdef _OC7IF

#define EnableIntOC7                    _OC7IE = 1
#define DisableIntOC7                   _OC7IE = 0
#define SetPriorityIntOC7(priority)     _OC7IP = priority

/*  CloseOC7    */
void CloseOC7() __attribute__ ((section (".libperi")));

/* ConfigIntOC7  */
void ConfigIntOC7(unsigned int config) __attribute__ ((section(".libperi")));

/*  OpenOC7   */
#if defined(__dsPIC33E__) || defined(__PIC24E__) 
void OpenOC7(unsigned int config1,unsigned int config2,unsigned int value1,
                 unsigned int value2) __attribute__ ((section (".libperi")));
#else
void OpenOC7(unsigned int config,unsigned int value1,
                 unsigned int value2) __attribute__ ((section (".libperi")));
#endif

/*  ReadDCOC7PWM    */
unsigned int ReadDCOC7PWM() __attribute__ ((section (".libperi")));

/*  ReadRegOC7    */
unsigned int ReadRegOC7(char reg) __attribute__ ((section(".libperi")));

/*  SetDCOC7PWM  */
#if defined(__dsPIC33E__) || defined(__PIC24E__) 
char SetDCOC7PWM(unsigned int dutycycle,unsigned int period) __attribute__((section (".libperi")));
#else
char SetDCOC7PWM(unsigned int dutycycle) __attribute__((section (".libperi")));
#endif

/*  SetPulseOC7    */
void SetPulseOC7(unsigned int pulse_start,unsigned int pulse_stop) __attribute__ 
((section (".libperi")));

#endif

#ifdef _OC8IF

#define EnableIntOC8                    _OC8IE = 1
#define DisableIntOC8                   _OC8IE = 0
#define SetPriorityIntOC8(priority)     _OC8IP = priority

/*  CloseOC8    */
void CloseOC8() __attribute__ ((section (".libperi")));

/* ConfigIntOC8  */
void ConfigIntOC8(unsigned int config) __attribute__ ((section(".libperi")));

/*  ReadDCOC8PWM    */
unsigned int ReadDCOC8PWM() __attribute__ ((section (".libperi")));

/*  ReadRegOC8    */
unsigned int ReadRegOC8(char reg) __attribute__ ((section(".libperi")));

/*  OpenOC8   */
#if defined(__dsPIC33E__) || defined(__PIC24E__) 
void OpenOC8(unsigned int config1,unsigned int config2,unsigned int value1,
                 unsigned int value2) __attribute__ ((section (".libperi")));
#else
void OpenOC8(unsigned int config,unsigned int value1,
                 unsigned int value2) __attribute__ ((section (".libperi")));
#endif

/*  SetDCOC8PWM  */
#if defined(__dsPIC33E__) || defined(__PIC24E__) 
char SetDCOC8PWM(unsigned int dutycycle,unsigned int period) __attribute__((section (".libperi")));
#else
char SetDCOC8PWM(unsigned int dutycycle) __attribute__((section (".libperi")));
#endif

/*  SetPulseOC8    */
void SetPulseOC8(unsigned int pulse_start,unsigned int pulse_stop) __attribute__ 
((section (".libperi")));

#endif

#ifdef _OC9IF

#define EnableIntOC9                    _OC9IE = 1
#define DisableIntOC9                   _OC9IE = 0
#define SetPriorityIntOC9(priority)     _OC9IP = priority

/*  CloseOC9    */
void CloseOC9() __attribute__ ((section (".libperi")));

/* ConfigIntOC9  */
void ConfigIntOC9(unsigned int config) __attribute__ ((section(".libperi")));

/*  ReadDCOC9PWM    */
unsigned int ReadDCOC9PWM() __attribute__ ((section (".libperi")));

/*  ReadRegOC9    */
unsigned int ReadRegOC9(char reg) __attribute__ ((section(".libperi")));

/*  OpenOC9   */
void OpenOC9(unsigned int config1,unsigned int config2,unsigned int value1,
                 unsigned int value2) __attribute__ ((section (".libperi")));

/*  SetDCOC9PWM  */
char SetDCOC9PWM(unsigned int dutycycle,unsigned int period) __attribute__ ((section(".libperi")));

/*  SetPulseOC9    */
void SetPulseOC9(unsigned int pulse_start,unsigned int pulse_stop) __attribute__ 
((section (".libperi")));

#endif

#ifdef _OC10IF

#define EnableIntOC10                    _OC10IE = 1
#define DisableIntOC10                   _OC10IE = 0
#define SetPriorityIntOC10(priority)     _OC10IP = priority

/*  CloseOC10    */
void CloseOC10() __attribute__ ((section (".libperi")));

/* ConfigIntOC10  */
void ConfigIntOC10(unsigned int config) __attribute__ ((section(".libperi")));

/*  ReadDCOC10PWM    */
unsigned int ReadDCOC10PWM() __attribute__ ((section (".libperi")));

/*  ReadRegOC10    */
unsigned int ReadRegOC10(char reg) __attribute__ ((section(".libperi")));

/*  OpenOC10   */
void OpenOC10(unsigned int config1,unsigned int config2,unsigned int value1,
                 unsigned int value2) __attribute__ ((section (".libperi")));

/*  SetDCOC10PWM  */
char SetDCOC10PWM(unsigned int dutycycle,unsigned int period) __attribute__ ((section(".libperi")));

/*  SetPulseOC10    */
void SetPulseOC10(unsigned int pulse_start,unsigned int pulse_stop) __attribute__ 
((section (".libperi")));

#endif

#ifdef _OC11IF

#define EnableIntOC11                    _OC11IE = 1
#define DisableIntOC11                   _OC11IE = 0
#define SetPriorityIntOC11(priority)     _OC11IP = priority

/*  CloseOC11    */
void CloseOC11() __attribute__ ((section (".libperi")));

/* ConfigIntOC11  */
void ConfigIntOC11(unsigned int config) __attribute__ ((section(".libperi")));

/*  ReadDCOC11PWM    */
unsigned int ReadDCOC11PWM() __attribute__ ((section (".libperi")));

/*  ReadRegOC11    */
unsigned int ReadRegOC11(char reg) __attribute__ ((section(".libperi")));

/*  OpenOC11   */
void OpenOC11(unsigned int config1,unsigned int config2,unsigned int value1,
                 unsigned int value2) __attribute__ ((section (".libperi")));

/*  SetDCOC11PWM  */
char SetDCOC11PWM(unsigned int dutycycle,unsigned int period) __attribute__ ((section(".libperi")));

/*  SetPulseOC11    */
void SetPulseOC11(unsigned int pulse_start,unsigned int pulse_stop) __attribute__ 
((section (".libperi")));

#endif


#ifdef _OC12IF

#define EnableIntOC12                    _OC12IE = 1
#define DisableIntOC12                   _OC12IE = 0
#define SetPriorityIntOC12(priority)     _OC12IP = priority

/*  CloseOC12    */
void CloseOC12() __attribute__ ((section (".libperi")));

/* ConfigIntOC12  */
void ConfigIntOC12(unsigned int config) __attribute__ ((section(".libperi")));

/*  ReadDCOC12PWM    */
unsigned int ReadDCOC12PWM() __attribute__ ((section (".libperi")));

/*  ReadRegOC12    */
unsigned int ReadRegOC12(char reg) __attribute__ ((section(".libperi")));

/*  OpenOC12   */
void OpenOC12(unsigned int config1,unsigned int config2,unsigned int value1,
                 unsigned int value2) __attribute__ ((section (".libperi")));

/*  SetDCOC12PWM  */
char SetDCOC12PWM(unsigned int dutycycle,unsigned int period) __attribute__ ((section(".libperi")));

/*  SetPulseOC12    */
void SetPulseOC12(unsigned int pulse_start,unsigned int pulse_stop) __attribute__ 
((section (".libperi")));

#endif

#ifdef _OC13IF

#define EnableIntOC13                    _OC13IE = 1
#define DisableIntOC13                   _OC13IE = 0
#define SetPriorityIntOC13(priority)     _OC13IP = priority

/*  CloseOC13    */
void CloseOC13() __attribute__ ((section (".libperi")));

/* ConfigIntOC13  */
void ConfigIntOC13(unsigned int config) __attribute__ ((section(".libperi")));

/*  ReadDCOC13PWM    */
unsigned int ReadDCOC13PWM() __attribute__ ((section (".libperi")));

/*  ReadRegOC13    */
unsigned int ReadRegOC13(char reg) __attribute__ ((section(".libperi")));

/*  OpenOC13   */
void OpenOC13(unsigned int config1,unsigned int config2,unsigned int value1,
                 unsigned int value2) __attribute__ ((section (".libperi")));

/*  SetDCOC13PWM  */
char SetDCOC13PWM(unsigned int dutycycle,unsigned int period) __attribute__ ((section(".libperi")));

/*  SetPulseOC13    */
void SetPulseOC13(unsigned int pulse_start,unsigned int pulse_stop) __attribute__ 
((section (".libperi")));

#endif

#ifdef _OC14IF

#define EnableIntOC14                    _OC14IE = 1
#define DisableIntOC14                   _OC14IE = 0
#define SetPriorityIntOC14(priority)     _OC14IP = priority

/*  CloseOC14    */
void CloseOC14() __attribute__ ((section (".libperi")));

/* ConfigIntOC14  */
void ConfigIntOC14(unsigned int config) __attribute__ ((section(".libperi")));

/*  ReadDCOC14PWM    */
unsigned int ReadDCOC14PWM() __attribute__ ((section (".libperi")));

/*  ReadRegOC14    */
unsigned int ReadRegOC14(char reg) __attribute__ ((section(".libperi")));

/*  OpenOC14   */
void OpenOC14(unsigned int config1,unsigned int config2,unsigned int value1,
                 unsigned int value2) __attribute__ ((section (".libperi")));

/*  SetDCOC14PWM  */
char SetDCOC14PWM(unsigned int dutycycle,unsigned int period) __attribute__ ((section(".libperi")));

/*  SetPulseOC14    */
void SetPulseOC14(unsigned int pulse_start,unsigned int pulse_stop) __attribute__ 
((section (".libperi")));

#endif

#ifdef _OC15IF

#define EnableIntOC15                    _OC15IE = 1
#define DisableIntOC15                   _OC15IE = 0
#define SetPriorityIntOC15(priority)     _OC15IP = priority

/*  CloseOC15    */
void CloseOC15() __attribute__ ((section (".libperi")));

/* ConfigIntOC15  */
void ConfigIntOC15(unsigned int config) __attribute__ ((section(".libperi")));

/*  ReadDCOC15PWM    */
unsigned int ReadDCOC15PWM() __attribute__ ((section (".libperi")));

/*  ReadRegOC15    */
unsigned int ReadRegOC15(char reg) __attribute__ ((section(".libperi")));

/*  OpenOC15   */
void OpenOC15(unsigned int config1,unsigned int config2,unsigned int value1,
                 unsigned int value2) __attribute__ ((section (".libperi")));

/*  SetDCOC15PWM  */
char SetDCOC15PWM(unsigned int dutycycle,unsigned int period) __attribute__ ((section(".libperi")));

/*  SetPulseOC15    */
void SetPulseOC15(unsigned int pulse_start,unsigned int pulse_stop) __attribute__ 
((section (".libperi")));

#endif

#ifdef _OC16IF

#define EnableIntOC16                    _OC16IE = 1
#define DisableIntOC16                   _OC16IE = 0
#define SetPriorityIntOC16(priority)     _OC16IP = priority

/*  CloseOC16    */
void CloseOC16() __attribute__ ((section (".libperi")));

/* ConfigIntOC16  */
void ConfigIntOC16(unsigned int config) __attribute__ ((section(".libperi")));

/*  ReadDCOC16PWM    */
unsigned int ReadDCOC16PWM() __attribute__ ((section (".libperi")));

/*  ReadRegOC16    */
unsigned int ReadRegOC16(char reg) __attribute__ ((section(".libperi")));

/*  OpenOC16   */
void OpenOC16(unsigned int config1,unsigned int config2,unsigned int value1,
                 unsigned int value2) __attribute__ ((section (".libperi")));

/*  SetDCOC16PWM  */
char SetDCOC16PWM(unsigned int dutycycle,unsigned int period) __attribute__ ((section(".libperi")));

/*  SetPulseOC16    */
void SetPulseOC16(unsigned int pulse_start,unsigned int pulse_stop) __attribute__ 
((section (".libperi")));

#endif


#endif
