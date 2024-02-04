#include "servo.h"
#include "stdio.h"

// function to initialize a new stepper providing its connection pins
Servo_t Servo_INIT() {
    // GPIO init for the pin 5.7 (the one attached to TA2.2 timer for PWM)
    GPIO_setAsPeripheralModuleFunctionOutputPin(GPIO_PORT_P5, GPIO_PIN7, GPIO_PRIMARY_MODULE_FUNCTION);

    // Timer A2.2 initialization
    Timer_A_configureUpMode(TIMER_A2_BASE, &servoTimerPWMConfig);
    Timer_A_startCounter(TIMER_A2_BASE, TIMER_A_UP_MODE);

    // returning a servo with its default values
    Servo_t servo =  {
        .compareConfig_PWM = {
            TIMER_A_CAPTURECOMPARE_REGISTER_2,          // Use CCR 2 to output on 5.7 pin
            TIMER_A_CAPTURECOMPARE_INTERRUPT_DISABLE,   // Disable CCR interrupt
            TIMER_A_OUTPUTMODE_TOGGLE_SET,              // Toggle output but
            SERVO_MIN_POSITION                          // Set to 0 position
        },
        .position=0,
        .increment=0,
        .current_time=0,
        .delay=SERVO_MIN_SPEED_DELAY
    };

    // starting the timer for PWM
    Timer_A_initCompare(TIMER_A2_BASE, &servo.compareConfig_PWM);
    return servo;
}

void Servo_setSpeed(Servo_t * servo, speed_t speed) {
    // set the direction (increment value positive or negative) of the servo
    if (speed > 0)
        servo->increment = 1;
    else if (speed < 0)
        servo->increment = -1;
    else
        servo->increment = 0;
    // set the speed adjusting the delay in a specified range between SERVO_MIN_SPEED_DELAY and SERVO_MAX_SPEED_DELAY 
    servo->delay = SERVO_MAX_SPEED_DELAY-((float) abs(speed) * (float) (SERVO_MIN_SPEED_DELAY) / (float) 100);
}

// function that move the motor only if it has to, according to the step delay. This function should be called inside an infinite loop
int Servo_tryMove(Servo_t * servo) {
    if (servo->current_time >= servo->delay) {
        
        servo->current_time = 0;

        // increment and bound check
        servo->position += servo->increment;
        if (servo->position > SERVO_MAX_POSITION)
            servo->position = SERVO_MAX_POSITION;
        if (servo->position < SERVO_MIN_POSITION)
            servo->position = SERVO_MIN_POSITION;
        
        // position update
        servo->compareConfig_PWM.compareValue = servo->position;
        // timer frequency update (it changes the PWM duty cycle to apply a new position to the stepper)
        Timer_A_initCompare(TIMER_A2_BASE, &servo->compareConfig_PWM);
        return 1;
    }
    else {
        // increase the time if the motor don't have to move
        servo->current_time++;
        return 0;
    }
}

// timer configuration for the servo main loop
extern const Timer_A_UpModeConfig Servo_timerConfig = {
        .clockSource = TIMER_A_CLOCKSOURCE_SMCLK,                                       // SMCLK Clock Source
        .clockSourceDivider = TIMER_A_CLOCKSOURCE_DIVIDER_4,                            // SMCLK/4 = 24MHz/4 = 6MHz
        .timerPeriod = 1500,                                                            // Timer period: 0.25ms
        .timerInterruptEnable_TAIE=TIMER_A_TAIE_INTERRUPT_DISABLE,                      // Disable Timer interrupt
        .captureCompareInterruptEnable_CCR0_CCIE= TIMER_A_CCIE_CCR0_INTERRUPT_ENABLE,   // Enable CCR0 interrupt
        .timerClear=TIMER_A_DO_CLEAR                                                    // Clear value
};

