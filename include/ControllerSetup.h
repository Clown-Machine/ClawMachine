#ifndef _CONTROLLER_SETUP_H_
#define _CONTROLLER_SETUP_H_

#include "params.h"
#include <ti/devices/msp432p4xx/inc/msp.h>
#include <ti/devices/msp432p4xx/driverlib/driverlib.h>
#include <ti/devices/msp432p4xx/driverlib/adc14.h>
#include <stdio.h>



/*
void Horizontal_setMessage();
void Vertical_setMessage();
*/

void hwInit();
void ledInit();
void timerInit();
void joystickInit();
void buttonInit();


#endif
