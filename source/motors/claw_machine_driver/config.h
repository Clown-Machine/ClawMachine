#ifndef CONFIG_H
#define CONFIG_H

#include "msp.h"
#include <ti/devices/msp432p4xx/driverlib/driverlib.h>

// definitions of all motors pins

// cart a dx motor
#define CART_A_DX_IN1 GPIO_PORT_P6, GPIO_PIN1
#define CART_A_DX_IN2 GPIO_PORT_P4, GPIO_PIN0
#define CART_A_DX_IN3 GPIO_PORT_P4, GPIO_PIN2
#define CART_A_DX_IN4 GPIO_PORT_P4, GPIO_PIN4
// cart a sx motor
#define CART_A_SX_IN1 GPIO_PORT_P6, GPIO_PIN4
#define CART_A_SX_IN2 GPIO_PORT_P6, GPIO_PIN5
#define CART_A_SX_IN3 GPIO_PORT_P4, GPIO_PIN6
#define CART_A_SX_IN4 GPIO_PORT_P1, GPIO_PIN5
// cart b dx motor
#define CART_B_DX_IN1 GPIO_PORT_P5, GPIO_PIN5
#define CART_B_DX_IN2 GPIO_PORT_P5, GPIO_PIN4
#define CART_B_DX_IN3 GPIO_PORT_P4, GPIO_PIN7
#define CART_B_DX_IN4 GPIO_PORT_P4, GPIO_PIN5
// cart b sc motor
#define CART_B_SX_IN1 GPIO_PORT_P2, GPIO_PIN3
#define CART_B_SX_IN2 GPIO_PORT_P5, GPIO_PIN1
#define CART_B_SX_IN3 GPIO_PORT_P3, GPIO_PIN5
#define CART_B_SX_IN4 GPIO_PORT_P3, GPIO_PIN7
// whinch motor
#define WHINCH_IN1 GPIO_PORT_P1, GPIO_PIN7
#define WHINCH_IN2 GPIO_PORT_P5, GPIO_PIN0
#define WHINCH_IN3 GPIO_PORT_P5, GPIO_PIN2
#define WHINCH_IN4 GPIO_PORT_P3, GPIO_PIN6

// servo position bounds
#define SERVO_MAX_POSITION 4000
#define SERVO_MIN_POSITION 1600

// servo speed bounds
#define SERVO_MAX_SPEED_DELAY 2
#define SERVO_MIN_SPEED_DELAY 16

// timers configuration
extern Timer_A_ContinuousModeConfig mainLoopTimerConfig;
extern Timer_A_UpModeConfig servoTimerPWMConfig;

// alias for speed type
typedef int8_t speed_t;

// alias for time type
typedef uint_fast64_t time_t;

// enum for the value to set on a pin
typedef enum {
    HIGH, LOW, TOGGLE
} PinValue_t;

// function to set the value of a pin using a parameter
void GPIO_setOutputOnPin(uint_fast8_t selectedPort, uint_fast16_t selectedPins, PinValue_t value);

#endif
