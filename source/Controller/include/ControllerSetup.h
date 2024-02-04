#ifndef _CONTROLLER_SETUP_H_
#define _CONTROLLER_SETUP_H_

#include <ti/devices/msp432p4xx/inc/msp.h>
#include <ti/devices/msp432p4xx/driverlib/driverlib.h>
#include <ti/devices/msp432p4xx/driverlib/adc14.h>
#include <stdio.h>

// void ledInit();

void hwInit();
void timerInit();
void joystickInit();
void buttonInit();
void controllerInit();

#endif
