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

#define T2_ON               0xffff      /* Timer1 ON */
#define T2_OFF              0x7fff      /* Timer1 OFF */

#define T2_IDLE_CON         0xdfff      /* operate during sleep */
#define T2_IDLE_STOP        0xffff      /* stop operation during sleep */

#define T2_GATE_ON          0xffff      /* Timer Gate time accumulation enabled */
#define T2_GATE_OFF         0xffbf      /* Timer Gate time accumulation disabled */

#define T2_PS_1_1           0xffcf      /* Prescaler 1:1 */
#define T2_PS_1_8           0xffdf      /*           1:8 */
#define T2_PS_1_64          0xffef      /*          1:64 */
#define T2_PS_1_256         0xffff      /*         1:256 */

#define T2_SYNC_EXT_ON      0xffff      /* Synch external clk input */
#define T2_SYNC_EXT_OFF     0xfffb      /* Do not synch external clk input */

#define T2_SOURCE_EXT       0xffff      /* External clock source */
#define T2_SOURCE_INT       0xfffd      /* Internal clock source */

/* defines for Timer Interrupts */

#define T2_INT_PRIOR_7      0xffff      /* 111 = Interrupt is priority 7 */
#define T2_INT_PRIOR_6      0xfffe      /* 110 = Interrupt is priority 6 */
#define T2_INT_PRIOR_5      0xfffd      /* 101 = Interrupt is priority 5 */
#define T2_INT_PRIOR_4      0xfffc      /* 100 = Interrupt is priority 4 */
#define T2_INT_PRIOR_3      0xfffb      /* 011 = Interrupt is priority 3 */
#define T2_INT_PRIOR_2      0xfffa      /* 010 = Interrupt is priority 2 */
#define T2_INT_PRIOR_1      0xfff9      /* 001 = Interrupt is priority 1 */
#define T2_INT_PRIOR_0      0xfff8      /* 000 = Interrupt is priority 0 */

#define T2_INT_ON           0xffff      /* Interrupt Enable */
#define T2_INT_OFF          0xfff7      /* Interrupt Disable */

/* Macros to  Enable/Disable interrupts and set Interrupt priority of Timers 1*/
#define EnableIntT2                    _T2IE = 1
#define DisableIntT2                   _T2IE = 0
#define SetPriorityIntT2(priority)     _T2IP = priority

/* Timer1 Function Prototypes */

/* OpenTimer1 */
void OpenTimer2( unsigned int config, unsigned int period); 
//(".libperi")));

/* CloseTimer1 */
void CloseTimer2(void);

/* ReadTimer1 */
unsigned int ReadTimer2(void); 

/* WriteTimer1 */
void WriteTimer2( unsigned int timer);

/* Config Int Timer1 */
void ConfigIntTimer2(unsigned int config);


#endif