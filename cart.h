#ifndef CART_H
#define CART_H

#include "stepper.h"

typedef struct {
    Stepper_t right_stepper;
    Stepper_t left_stepper;

    uint32_t position;
} Cart_t;

Cart_t Cart_INIT(Stepper_t right, Stepper_t left);

void Cart_setSpeed_Percentage(Cart_t * cart, speed_t speed_percentage);
void Cart_tryMove(Cart_t * cart);
int Cart_goTo(Cart_t * cart, uint32_t position);

#endif
