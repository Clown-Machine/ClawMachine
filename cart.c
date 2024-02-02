#include "cart.h"
#include "stdio.h"

Cart_t Cart_INIT(Stepper_t right, Stepper_t left) {
    return (Cart_t) {
        .right_stepper = right,
        .left_stepper = left,
        .position = 0
    };
}

void Cart_setSpeed_Percentage(Cart_t * cart, speed_t speed_percentage) {
    //printf("setting speed to cart\n");
    Stepper_setSpeed_Percentage(&cart->right_stepper, speed_percentage);
    Stepper_setSpeed_Percentage(&cart->left_stepper, -speed_percentage);
}

void Cart_tryMove(Cart_t * cart) {
    Stepper_tryMove(&cart->left_stepper);
    if (Stepper_tryMove(&cart->right_stepper)) {
        cart->position += cart->right_stepper.direction == CLOCKWISE ? 1 : -1; // set the position according to the direction of the right motor: the driving one.
    }
}

int Cart_goTo(Cart_t * cart, uint32_t position) {

    if (position > cart->position) { // the cart should go forward
        Cart_setSpeed_Percentage(cart, 50);
    }
    else if (position < cart->position) { // the cart should go backward
        Cart_setSpeed_Percentage(cart, -50);
    }
    else { // if the two positions are equals the cart should stop
        Cart_setSpeed_Percentage(cart, 0);
        return 1;
    }

    Cart_tryMove(cart);

    return 0;
}


