#include "stdlib.h"
#include "stdio.h"

#include "stepper.h"

const int MIN_SPEED_DELAY = 20; // the delay to spin a stepper at its minimum speed 20 extra tick to wait, 5ms period
const int MAX_SPEED_DELAY = 10; // the delay to spin a stepper at its maximum speed. 10 extra tick to wait, 2.5ms period

// data structure to represent a motor step: it stores the value the four coils should have at that specific step
typedef struct Step_t {
    PinValue_t COIL1_Value;
    PinValue_t COIL2_Value;
    PinValue_t COIL3_Value;
    PinValue_t COIL4_Value;
} Step_t;

// function that store the four steps to properly spin the motor.
Step_t step(StepNumber_t stepNumber) {
    switch(stepNumber) {                                // Step COIL_1  COIL_2  COIL_3  COIL_4
        case 0:
            return (Step_t) {HIGH, HIGH, LOW, LOW};     // 0    HIGH    LOW     HIGH    LOW
        case 1:
            return (Step_t) {LOW, HIGH, HIGH, LOW};     // 1    LOW     HIGH    HIGH    LOW
        case 2:
            return (Step_t) {LOW, LOW, HIGH, HIGH};     // 2    LOW     HIGH    LOW     HIGH
        case 3:
            return (Step_t) {HIGH, LOW, LOW, HIGH};     // 3    HIGH    LOW     LOW     HIGH
        default:
            return (Step_t) {LOW, LOW, LOW, LOW};
    }
}

// function to initialize a new stepper providing its connection pins
Stepper_t Stepper_INIT(uint_fast8_t coil1_port, uint_fast8_t coil1_pin,
                         uint_fast8_t coil2_port, uint_fast8_t coil2_pin,
                         uint_fast8_t coil3_port, uint_fast8_t coil3_pin,
                         uint_fast8_t coil4_port, uint_fast8_t coil4_pin) {

    // GPIO initialization for the stepper pins
    GPIO_setAsOutputPin(coil1_port, coil1_pin);
    GPIO_setAsOutputPin(coil2_port, coil2_pin);
    GPIO_setAsOutputPin(coil3_port, coil3_pin);
    GPIO_setAsOutputPin(coil4_port, coil4_pin);

    // returning the stepper with its default values
    return (Stepper_t) {
        .COIL1_Port = coil1_port,
        .COIL1_Pin = coil1_pin,
        .COIL2_Port = coil2_port,
        .COIL2_Pin = coil2_pin,
        .COIL3_Port = coil3_port,
        .COIL3_Pin = coil3_pin,
        .COIL4_Port = coil4_port,
        .COIL4_Pin = coil4_pin,
        .step_delay = MIN_SPEED_DELAY, 
        .current_time = 0,
        .time_increment = 1, // default should be 500
        .number_of_steps = 2048, // number of steps for a 360 degree rotation
        .current_step = 0, 
        .direction = STATIONARY // by default the motor does not move
    };
}

// function to set the speed of the stepper using a percentage value
void Stepper_setSpeed(Stepper_t * stepper, speed_t speed_percentage) {
    // set the speed adjusting the delay in a specified range between MIN_SPEED_DELAY and MAX_SPEED_DELAY
    stepper->step_delay = MIN_SPEED_DELAY - ((float) abs(speed_percentage) * (float) (MIN_SPEED_DELAY-MAX_SPEED_DELAY) / (float) 100);
    // sets the direction of the stepper since the delay is a only-positive integer
    if(speed_percentage > 0)
        stepper->direction = CLOCKWISE;
    else if(speed_percentage < 0)
        stepper->direction = COUNTERCLOCKWISE;
    else {
        stepper->direction = STATIONARY;
        // set all the pins to low when the stepper is stopped in order to save energy
        GPIO_setOutputOnPin(stepper->COIL1_Port, stepper->COIL1_Pin, LOW);
        GPIO_setOutputOnPin(stepper->COIL2_Port, stepper->COIL2_Pin, LOW);
        GPIO_setOutputOnPin(stepper->COIL3_Port, stepper->COIL3_Pin, LOW);
        GPIO_setOutputOnPin(stepper->COIL4_Port, stepper->COIL4_Pin, LOW);
    }
}

// function which increment the time and determine if the stepper should move or not
uint_fast8_t Stepper_shouldMoveAfterIncrement(Stepper_t * stepper) {
    stepper->current_time+=stepper->time_increment;
    if (stepper->current_time >= stepper->step_delay) { // check if enough time has passed since the last step (the length of a step determine the rotation speed)
        stepper->current_time = 0; // resets the current time to zero
        return 1;
    }
    return 0;
}

// function that move the motor only if it has to according to the step delay. Returns 1 if the motor moved, 0 otherwise. This function should be called in an infinite loop. 
int Stepper_tryMove(Stepper_t * stepper) {
    if(Stepper_shouldMoveAfterIncrement(stepper) && stepper->direction != STATIONARY) {
        //printf("apply\n");
        int8_t increment = stepper->direction == CLOCKWISE ? 1 : -1;
        stepper->current_step = (stepper->current_step+increment)%4;
        if(stepper->current_step < 0)
            stepper->current_step = 3;

        Step_t currentStep = step(stepper->current_step);
        GPIO_setOutputOnPin(stepper->COIL1_Port, stepper->COIL1_Pin, currentStep.COIL1_Value);
        GPIO_setOutputOnPin(stepper->COIL2_Port, stepper->COIL2_Pin, currentStep.COIL2_Value);
        GPIO_setOutputOnPin(stepper->COIL3_Port, stepper->COIL3_Pin, currentStep.COIL3_Value);
        GPIO_setOutputOnPin(stepper->COIL4_Port, stepper->COIL4_Pin, currentStep.COIL4_Value);
        return 1;
    }
    else {
        return 0;
    }
}

// timer configuration for the stepper main loop
const Timer_A_UpModeConfig timerConfig = {
        .clockSource = TIMER_A_CLOCKSOURCE_SMCLK,                                       // SMCLK Clock Source
        .clockSourceDivider = TIMER_A_CLOCKSOURCE_DIVIDER_4,                            // SMCLK/4 = 24MHz/4 = 6MHz
        .timerPeriod = 1500,                                                            // Timer period: 0.25ms
        .timerInterruptEnable_TAIE=TIMER_A_TAIE_INTERRUPT_DISABLE,                      // Disable Timer interrupt
        .captureCompareInterruptEnable_CCR0_CCIE= TIMER_A_CCIE_CCR0_INTERRUPT_ENABLE,   // Enable CCR0 interrupt
        .timerClear=TIMER_A_DO_CLEAR                                                    // Clear value
};
