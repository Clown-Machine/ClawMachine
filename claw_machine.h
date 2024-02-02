#ifndef CLAW_MACHINE_H
#define CLAW_MACHINE_H

#include "cart.h"
#include "servo.h"

typedef struct
{
    uint32_t x;
    uint32_t y;
} Position_t;

typedef struct
{
    Position_t target;
} TargetMode_t;

typedef struct
{
    // no parameters
} ManualMode_t;

typedef struct
{
    enum
    {
        MANUAL_MODE,
        TARGET_MODE
    } tag;
    union
    {
        TargetMode_t target_mode;
        ManualMode_t manual_mode;
    } data;
} Mode_t;

typedef struct
{
    Cart_t cart_a;
    Cart_t cart_b;

    Stepper_t whinch;
    Servo_t gripper;

    Mode_t mode;
} ClawMachine_t;

ClawMachine_t Claw_INIT(Cart_t cart_a, Cart_t cart_b, Stepper_t whinch);

Position_t Claw_getCurrentPosition(ClawMachine_t *clawMachine);

void Claw_setTargetMode(ClawMachine_t *clawMachine, Position_t position);
void Claw_setManualMode(ClawMachine_t *clawMachine);

void Claw_setXSpeed(ClawMachine_t *clawMachine, speed_t speed);
void Claw_setYSpeed(ClawMachine_t *clawMachine, speed_t speed);
void Claw_setZSpeed(ClawMachine_t *clawMachine, speed_t speed);
void Claw_setGripperSpeed(ClawMachine_t *clawMachine, speed_t speed);

int Claw_tryMove(ClawMachine_t *clawMachine);

#endif
