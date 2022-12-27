#include "timer2.h"
#include<p30fxxxx.h>
#ifdef _T2IF
/********************************************************************
*    Function Name:  CloseTimer2                                    *
*    Description:    This routine disables the Timer2 and its       *
*                    interrupt and flag bits.                       *
*    Parameters:     None                                           *
*    Return Value:   None                                           *
********************************************************************/

void CloseTimer2(void)
{
    _T2IE = 0;      /* Disable the Timer2 interrupt */
    T2CONbits.TON = 0;      /* Disable timer2 */
    _T2IF = 0;      /* Clear Timer interrupt flag */
}


/*******************************************************************
*    Function Name: ConfigIntTimer2                                *
*    Description:   This function configures interrupt and sets    *
*                   Interrupt Priority                             *
*    Parameters:    unsigned int config                            *
*    Return Value:  None                                           *
*******************************************************************/

void ConfigIntTimer2(unsigned int config)
{
    _T2IF = 0;                   /* clear IF bit */
    _T2IP = (config &0x0007);    /* assigning Interrupt Priority */
    _T2IE = (config &0x0008)>>3; /* Interrupt Enable /Disable */
}

/********************************************************************
*    Function Name:  OpenTimer2                                     *
*    Description:    This routine configures the timer control      *
*                    register and timer period register.            *
*    Parameters:     config: bit definitions to configure Timer2    *
*                    period: value to be loaded to PR reg           *
*    Return Value:   None                                           *
********************************************************************/

void OpenTimer2(unsigned int config,unsigned int period)
{
    TMR2  = 0;          /* Reset Timer2 to 0x0000 */
    PR2   = period;     /* assigning Period to Timer period register */
    T2CON = config;     /* configure control reg */
    T2CONbits.T32 = 0;
}

/********************************************************************
*    Function Name:  ReadTimer2                                     *
*    Description:    This routine reads the 16-bit value from       *
*                    Timer2 Register.                               *
*    Parameters:     None                                           *
*    Return Value:   unsigned int: Timer  16-bit value              *
********************************************************************/

unsigned int ReadTimer2(void)
{
    return (TMR2);      /* Return the Timer2 register */
}


/********************************************************************
*    Function Name:  WriteTimer2                                    *
*    Description:    This routine writes a 16-bit value to Timer2   *
*    Parameters:     unsigned int: value to write to Timer          *
*    Return Value:   None                                           *
********************************************************************/

void WriteTimer2(unsigned int timer)
{
    TMR2 = timer;     /* assign timer value to Timer2 Register */
}



#else 
#warning "Does not build on this target"
#endif