#ifndef ADC_H
#define	ADC_H

#ifdef	__cplusplus
extern "C" {
#endif

#include<p30fxxxx.h>

//void ADCinit_analog(void);
void ADCinit(void);
void ConfigureADCPins(void);
void ADCinit_analog(void);
//void ADCinit(void);


#ifdef	__cplusplus
}
#endif

#endif	/* ADC_H */

