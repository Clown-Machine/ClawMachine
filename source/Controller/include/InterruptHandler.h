#ifndef _INTERRUPT_H_
#define _INTERRUPT_H_

#include <Controller/include/ControllerFSM.h>
#include <ti/devices/msp432p4xx/inc/msp.h>
#include <ti/devices/msp432p4xx/driverlib/driverlib.h>
#include <ti/devices/msp432p4xx/driverlib/adc14.h>
#include <stdio.h>

void TA1_N_IRQHandler();
void ADC14_IRQHandler();
void PORT5_IRQHandler();
void PORT4_IRQHandler();
void PORT3_IRQHandler();

#endif
