#ifndef CART_H
#define CART_H

#include "hardware/stepper.h"

// Library to move a claw machine cart (consisting of two stepper motors spinning in the opposite direction).
// This library also track the cart position (relative to the starting point) and allows to tell the cart to go at a specific location

// a cart is made up of two stepper and its position
typedef struct {
    Stepper_t right_stepper;
    Stepper_t left_stepper;

    uint32_t position;
} Cart_t;

// initialize a new cart given its two motors
Cart_t Cart_INIT(Stepper_t right, Stepper_t left);

// sets the speed of the cart by a percentage value
void Cart_setSpeed_Percentage(Cart_t * cart, speed_t speed_percentage);

// function to tell the motor to go to a specific position. It automatically sets the speed and move the motor in the right direction. This function should be called inside an infinite loop
int Cart_goTo(Cart_t * cart, uint32_t position);
// function that move the cart only if it has to according to its motor status. This function should be called inside an infinite loop
void Cart_tryMove(Cart_t * cart);

#endif
