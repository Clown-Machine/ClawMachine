#ifndef SERVO_H
#define SERVO_H

#include "msp.h"
#include <ti/devices/msp432p4xx/driverlib/driverlib.h>

#include "config.h"
#include "global.h"

typedef struct {
    Timer_A_CompareModeConfig compareConfig_PWM;
    uint32_t position;
    int32_t increment;
    uint32_t current_time;
    uint32_t delay;
} Servo_t;

Servo_t Servo_INIT();
void Servo_setSpeed(Servo_t * servo, speed_t speed);
int Servo_tryMove(Servo_t * servo);

#endif
