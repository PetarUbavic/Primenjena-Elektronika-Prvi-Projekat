#include "timer3.h"
#include<p30fxxxx.h>
#ifdef _T3IF
/********************************************************************
*    Function Name:  CloseTimer2                                    *
*    Description:    This routine disables the Timer2 and its       *
*                    interrupt and flag bits.                       *
*    Parameters:     None                                           *
*    Return Value:   None                                           *
********************************************************************/

void CloseTimer3(void)
{
    _T3IE = 0;      /* Disable the Timer2 interrupt */
    T3CONbits.TON = 0;      /* Disable timer2 */
    _T3IF = 0;      /* Clear Timer interrupt flag */
}


/*******************************************************************
*    Function Name: ConfigIntTimer2                                *
*    Description:   This function configures interrupt and sets    *
*                   Interrupt Priority                             *
*    Parameters:    unsigned int config                            *
*    Return Value:  None                                           *
*******************************************************************/

void ConfigIntTimer3(unsigned int config)
{
    _T3IF = 0;                   /* clear IF bit */
    _T3IP = (config &0x0007);    /* assigning Interrupt Priority */
    _T3IE = (config &0x0008)>>3; /* Interrupt Enable /Disable */
}

/********************************************************************
*    Function Name:  OpenTimer2                                     *
*    Description:    This routine configures the timer control      *
*                    register and timer period register.            *
*    Parameters:     config: bit definitions to configure Timer2    *
*                    period: value to be loaded to PR reg           *
*    Return Value:   None                                           *
********************************************************************/

void OpenTimer3(unsigned int config,unsigned int period)
{
    TMR3  = 0;          /* Reset Timer2 to 0x0000 */
    PR3   = period;     /* assigning Period to Timer period register */
    T3CON = config;     /* configure control reg */
    //T3CONbits.T32 = 0;
}

/********************************************************************
*    Function Name:  ReadTimer2                                     *
*    Description:    This routine reads the 16-bit value from       *
*                    Timer2 Register.                               *
*    Parameters:     None                                           *
*    Return Value:   unsigned int: Timer  16-bit value              *
********************************************************************/

unsigned int ReadTimer3(void)
{
    return (TMR3);      /* Return the Timer2 register */
}


/********************************************************************
*    Function Name:  WriteTimer2                                    *
*    Description:    This routine writes a 16-bit value to Timer2   *
*    Parameters:     unsigned int: value to write to Timer          *
*    Return Value:   None                                           *
********************************************************************/

void WriteTimer3(unsigned int timer)
{
    TMR3 = timer;     /* assign timer value to Timer2 Register */
}



#else 
#warning "Does not build on this target"
#endif