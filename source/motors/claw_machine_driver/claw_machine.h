#ifndef CLAW_MACHINE_H
#define CLAW_MACHINE_H

#include "cart.h"
#include "hardware/servo.h"

// Library to manage a claw machine movements (x_axis, y_axis, z_axis and gripper opening and closing). 
// A claw machine can act in two different modes: manual mode and target mode. 
// - in target mode the machine moves only in the horizontal axes (x and y) to a specific target. Targets are set by moving to a specific location and saving the current position using the Claw_updateTargetValue function.
// - in manal mode the user manually sets the speed of each motor 

// define the position struct used for moving the claw machine to a specific position 
typedef struct
{
    uint32_t x;
    uint32_t y;
} Position_t;

// define the data for the target mode
typedef struct
{
    Position_t target;
} TargetMode_t;

// define the data for the manual mode
typedef struct
{
    // no parameters
} ManualMode_t;

// define the data for a generic mode. The tag indicates in which mode the claw machine is operating in, the data field is a union containing the data of the current mode
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

// struct with all data for a claw machine
typedef struct
{
    Cart_t cart_a; // main cart (Y axis)
    Cart_t cart_b; // second cart (X axis)

    Stepper_t whinch; // whinch motor (Z axis)
    Servo_t gripper; // gripper motor

    Mode_t mode; // current mode with its data

    Position_t targets[4]; // array of saved targets
} ClawMachine_t;

// init the claw machine providing its motors
ClawMachine_t Claw_INIT(Cart_t cart_a, Cart_t cart_b, Stepper_t whinch);

// returns the current position of the claw machine (only horizontal coordinates)
Position_t Claw_getCurrentPosition(ClawMachine_t *clawMachine);

// function to change a target given its index. This function overwrite the given target with the current claw position
void Claw_updateTargetValue(ClawMachine_t *clawMachine, uint8_t position_number);

// move the claw machine to a specific target given its index
void Claw_setTargetMode(ClawMachine_t *clawMachine, uint8_t position_number);
// sets the claw machine to manual mode
void Claw_setManualMode(ClawMachine_t *clawMachine);

// put the claw machine in manual mode and sets the X axis speed using a percentage value
void Claw_setXSpeed(ClawMachine_t *clawMachine, speed_t speed);
// put the claw machine in manual mode and sets the Y axis speed using a percentage value
void Claw_setYSpeed(ClawMachine_t *clawMachine, speed_t speed);
// put the claw machine in manual mode and sets the Z axis speed using a percentage value 
void Claw_setZSpeed(ClawMachine_t *clawMachine, speed_t speed);
// put the claw machine in manual mode and sets the gripper speed using a percentage value 
void Claw_setGripperSpeed(ClawMachine_t *clawMachine, speed_t speed);

// function that move the claw machine only if it has to according to its motor status. This function should be called inside an infinite loop
void Claw_tryMove(ClawMachine_t *clawMachine);

#endif
