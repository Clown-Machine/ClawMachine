#include "servo.h"
#include "stdio.h"

Servo_t Servo_INIT() {
    GPIO_setAsPeripheralModuleFunctionOutputPin(GPIO_PORT_P5, GPIO_PIN7, GPIO_PRIMARY_MODULE_FUNCTION);

    Timer_A_configureUpMode(TIMER_A2_BASE, &servoTimerPWMConfig);
    Timer_A_startCounter(TIMER_A2_BASE, TIMER_A_UP_MODE);

    Servo_t servo =  {
        .compareConfig_PWM = {
            TIMER_A_CAPTURECOMPARE_REGISTER_2,          // Use CCR
            TIMER_A_CAPTURECOMPARE_INTERRUPT_DISABLE,   // Disable CCR interrupt
            TIMER_A_OUTPUTMODE_TOGGLE_SET,              // Toggle output but
            SERVO_MIN_POSITION                          // 25% Duty Cycle initially
        },
        .position=0,
        .increment=0,
        .current_time=0,
        .delay=SERVO_MIN_SPEED_DELAY
    };
    Timer_A_initCompare(TIMER_A2_BASE, &servo.compareConfig_PWM);
    return servo;
}

// MAX_SPEED:x=100:speed
void Servo_setSpeed(Servo_t * servo, speed_t speed) {
    if (speed > 0)
        servo->increment = 1;
    else if (speed < 0)
        servo->increment = -1;
    else
        servo->increment = 0;

    servo->delay = 32-((float) abs(speed) * (float) (SERVO_MIN_SPEED_DELAY) / (float) 100);
}

int Servo_tryMove(Servo_t * servo) {
    if (servo->current_time >= servo->delay) {
        //printf("%d %d %d\n", servo->current_time, servo->delay, servo->increment);
        servo->current_time = 0;

        servo->position += servo->increment;
        if (servo->position > SERVO_MAX_POSITION)
            servo->position = SERVO_MAX_POSITION;
        if (servo->position < SERVO_MIN_POSITION)
            servo->position = SERVO_MIN_POSITION;

        servo->compareConfig_PWM.compareValue = servo->position;
        Timer_A_initCompare(TIMER_A2_BASE, &servo->compareConfig_PWM);
        return 1;
    }
    else {
        servo->current_time++;
        return 0;
    }
}
