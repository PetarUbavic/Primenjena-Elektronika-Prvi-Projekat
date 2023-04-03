/********************************************************************/
/*              Header for Timer module library functions           */
/********************************************************************/

#if defined(__dsPIC30F__)
#include <p30fxxxx.h>

#endif 

#ifndef TIMER_H
#define TIMER_H

/* List of SFRs for Timers */
/* This list contains the SFRs with default (POR) values to be used for configuring Timers */
/* The user can modify this based on the requirement */
#define TMRx_VALUE          0x0000
#define PRx_VALUE           0xFFFF
#define TxCON_VALUE         0x0000

/* Timer1 Control Register (T1CON) Bit Defines */

#define T3_ON               0xffff      /* Timer1 ON */
#define T3_OFF              0x7fff      /* Timer1 OFF */

#define T3_IDLE_CON         0xdfff      /* operate during sleep */
#define T3_IDLE_STOP        0xffff      /* stop operation during sleep */

#define T3_GATE_ON          0xffff      /* Timer Gate time accumulation enabled */
#define T3_GATE_OFF         0xffbf      /* Timer Gate time accumulation disabled */

#define T3_PS_1_1           0xffcf      /* Prescaler 1:1 */
#define T3_PS_1_8           0xffdf      /*           1:8 */
#define T3_PS_1_64          0xffef      /*          1:64 */
#define T3_PS_1_256         0xffff      /*         1:256 */

#define T3_SYNC_EXT_ON      0xffff      /* Synch external clk input */
#define T3_SYNC_EXT_OFF     0xfffb      /* Do not synch external clk input */

#define T3_SOURCE_EXT       0xffff      /* External clock source */
#define T3_SOURCE_INT       0xfffd      /* Internal clock source */

/* defines for Timer Interrupts */

#define T3_INT_PRIOR_7      0xffff      /* 111 = Interrupt is priority 7 */
#define T3_INT_PRIOR_6      0xfffe      /* 110 = Interrupt is priority 6 */
#define T3_INT_PRIOR_5      0xfffd      /* 101 = Interrupt is priority 5 */
#define T3_INT_PRIOR_4      0xfffc      /* 100 = Interrupt is priority 4 */
#define T3_INT_PRIOR_3      0xfffb      /* 011 = Interrupt is priority 3 */
#define T3_INT_PRIOR_2      0xfffa      /* 010 = Interrupt is priority 2 */
#define T3_INT_PRIOR_1      0xfff9      /* 001 = Interrupt is priority 1 */
#define T3_INT_PRIOR_0      0xfff8      /* 000 = Interrupt is priority 0 */

#define T3_INT_ON           0xffff      /* Interrupt Enable */
#define T3_INT_OFF          0xfff7      /* Interrupt Disable */

/* Macros to  Enable/Disable interrupts and set Interrupt priority of Timers 1*/
#define EnableIntT3                    _T3IE = 1
#define DisableIntT3                   _T3IE = 0
#define SetPriorityIntT3(priority)     _T3IP = priority

/* Timer1 Function Prototypes */

/* OpenTimer1 */
void OpenTimer3( unsigned int config, unsigned int period); 
//(".libperi")));

/* CloseTimer1 */
void CloseTimer3(void);

/* ReadTimer1 */
unsigned int ReadTimer3(void); 

/* WriteTimer1 */
void WriteTimer3( unsigned int timer);

/* Config Int Timer1 */
void ConfigIntTimer3(unsigned int config);


#endif