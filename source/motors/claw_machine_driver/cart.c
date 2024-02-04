#include "cart.h"
#include "stdio.h"

// cart initialization
Cart_t Cart_INIT(Stepper_t right, Stepper_t left) {
    return (Cart_t) {
        .right_stepper = right,
        .left_stepper = left,
        .position = 0
    };
}

// sets the speed to the cart's motors. They should spin at the same speed but opposite direction
void Cart_setSpeed(Cart_t * cart, speed_t speed_percentage) {
    Stepper_setSpeed(&cart->right_stepper, speed_percentage);
    Stepper_setSpeed(&cart->left_stepper, -speed_percentage);
}

// move the motors and track the position. It increments the position only when a motor moves because motors may spin at different times and steps could be counted twice
void Cart_tryMove(Cart_t * cart) {
    Stepper_tryMove(&cart->left_stepper);
    if (Stepper_tryMove(&cart->right_stepper)) {
        cart->position += cart->right_stepper.direction == CLOCKWISE ? 1 : -1; // set the position according to the direction of the right motor: the driving one.
    }
}

// move the cart to a specific position (at the maximum speed). Returns 1 if the cart reached the target, 0 otherwise
int Cart_goTo(Cart_t * cart, uint32_t position) {

    // set the speed according to the direction of the target
    if (position > cart->position) { // the cart should go forward
        Cart_setSpeed(cart, 100);
    }
    else if (position < cart->position) { // the cart should go backward
        Cart_setSpeed(cart, -100);
    }
    else { // if the two positions are equals the cart should stop
        Cart_setSpeed(cart, 0);
        return 1;
    }

    // moves the cart at the right speed
    Cart_tryMove(cart);

    return 0;
}
