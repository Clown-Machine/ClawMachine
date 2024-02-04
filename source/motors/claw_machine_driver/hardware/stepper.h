#ifndef STEPPER_H
#define STEPPER_H

#include "../config.h"

#include "msp.h"
#include <ti/devices/msp432p4xx/driverlib/driverlib.h>

// Library to manage a stepper motor:
// in order to correctly use the library you should follow the steps below:
// 1) init the stepper using the INIT function
// 2) init a timer using the configuration provided by the library (it assumes SMCLK to be at 24MHz)
// 3) call TryMove inside the timer event
// 4) set the speed from the outside in order to actually move the motor

// enum to know in which direction is the stepper spinning
typedef enum {
    STATIONARY,
    CLOCKWISE,
    COUNTERCLOCKWISE
} direction_t;

// alias for the number of steps type
typedef int8_t StepNumber_t;

// struct that keeps all information of a stepper motor
typedef struct {
    // stepper connection pins
    uint_fast8_t COIL1_Port;
    uint_fast8_t COIL1_Pin;
    uint_fast8_t COIL2_Port;
    uint_fast8_t COIL2_Pin;
    uint_fast8_t COIL3_Port;
    uint_fast8_t COIL3_Pin;
    uint_fast8_t COIL4_Port;
    uint_fast8_t COIL4_Pin;

    time_t step_delay;
    time_t current_time;
    time_t time_increment;

    direction_t direction;

    uint_fast32_t number_of_steps;

    StepNumber_t current_step;
} Stepper_t;

// function to initialize a new stepper providing its connection pins
Stepper_t Stepper_INIT(uint_fast8_t coil1_port, uint_fast8_t coil1_pin,
                         uint_fast8_t coil2_port, uint_fast8_t coil2_pin,
                         uint_fast8_t coil3_port, uint_fast8_t coil3_pin,
                         uint_fast8_t coil4_port, uint_fast8_t coil4_pin);

// timer configuration for the stepper main loop
extern const Timer_A_UpModeConfig timerConfig;

// function to set the speed of the stepper using a percentage value
void Stepper_setSpeed(Stepper_t * stepper, speed_t speed_percentage);
// function which increment the time and determine if the stepper should move or not
int Stepper_tryMove(Stepper_t * stepper);

#endif
