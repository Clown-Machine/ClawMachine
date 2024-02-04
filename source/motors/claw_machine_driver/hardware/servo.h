#ifndef SERVO_H
#define SERVO_H

#include "msp.h"
#include <ti/devices/msp432p4xx/driverlib/driverlib.h>

#include "../config.h"

// Library to manage a servo motor by providing its rotation speed:
// in order to correctly use the library you should follow the steps below:
// 1) init the servo using the INIT function (this library assumes that the servo is connected to the 5.7 pin)
// 2) init a timer using the configuration provided by the library (it assumes SMCLK to be at 24MHz)
// 3) call TryMove inside the timer event
// 4) set the speed from the outside in order to actually move the motor

// struct that keeps all information of a servo motor
typedef struct {
    Timer_A_CompareModeConfig compareConfig_PWM;
    uint32_t position;
    int32_t increment;
    uint32_t current_time;
    uint32_t delay;
} Servo_t;

// function to initialize a new stepper providing its connection pins
Servo_t Servo_INIT();

// function to set the speed of the stepper using a percentage value
void Servo_setSpeed(Servo_t * servo, speed_t speed);
// function that move the motor only if it has to, according to the step delay. This function should be called in an infinite loop
int Servo_tryMove(Servo_t * servo);

// timer configuration for the stepper main loop
extern const Timer_A_UpModeConfig Servo_timerConfig;

#endif
