#include "claw_machine.h"
#include "cart.h"

// claw machine initialization at its default values
ClawMachine_t Claw_INIT(Cart_t cart_a, Cart_t cart_b, Stepper_t whinch)
{
    ManualMode_t data = (ManualMode_t){};

    return (ClawMachine_t){
        .cart_a = cart_a,
        .cart_b = cart_b,
        .whinch = whinch,
        .gripper = Servo_INIT(),
        .mode = (Mode_t){
            .tag = MANUAL_MODE,
            .data.manual_mode = data,
        },
        // default targets are the four corners
        .targets = {
            {0,0},
            {3000,0},
            {3000,3000},
            {0,3000}
        }
    };
}
// set the given target to the current position
void Claw_updateTargetValue(ClawMachine_t *clawMachine, uint8_t position_number) {
    clawMachine->targets[position_number] = Claw_getCurrentPosition(clawMachine);
}
// set the claw machine to target mode passing the destination
void Claw_setTargetMode(ClawMachine_t *clawMachine, uint8_t position)
{
    // stop Z and gripper motors 
    Claw_setZSpeed(clawMachine, 0);
    Claw_setGripperSpeed(clawMachine, 0);

    // init data for target mode
    TargetMode_t data = (TargetMode_t) {
        .target = clawMachine->targets[position]
    };

    // update claw machine mode field
    clawMachine->mode = (Mode_t){
        .tag = TARGET_MODE,
        .data = data,
    };
}

// sets the claw machine to manual mode
void Claw_setManualMode(ClawMachine_t *clawMachine)
{
    clawMachine->mode = (Mode_t) {
        .tag = MANUAL_MODE,
        .data = 0
    };
}

void Claw_setXSpeed(ClawMachine_t *clawMachine, speed_t speed)
{
    Claw_setManualMode(clawMachine);
    Cart_setSpeed(&clawMachine->cart_b, speed);
}

void Claw_setYSpeed(ClawMachine_t *clawMachine, speed_t speed)
{
    Claw_setManualMode(clawMachine);
    Cart_setSpeed(&clawMachine->cart_a, speed);
}

void Claw_setZSpeed(ClawMachine_t *clawMachine, speed_t speed)
{
    Claw_setManualMode(clawMachine);
    Stepper_setSpeed(&clawMachine->whinch, speed);
}

void Claw_setGripperSpeed(ClawMachine_t *clawMachine, speed_t speed)
{
    Claw_setManualMode(clawMachine);
    Servo_setSpeed(&clawMachine->gripper, speed);
}

// returns the current position of the claw machine
Position_t Claw_getCurrentPosition(ClawMachine_t *clawMachine)
{
    return (Position_t){
        clawMachine->cart_b.position,
        clawMachine->cart_a.position};
}

// move the claw machine according to its status and its motor status
void Claw_tryMove(ClawMachine_t *clawMachine)
{
    if (clawMachine->mode.tag == TARGET_MODE)
    {
        // if in target mode move the two carts to their respective target
        int res1 = Cart_goTo(&clawMachine->cart_b, clawMachine->mode.data.target_mode.target.x);
        int res2 = Cart_goTo(&clawMachine->cart_a, clawMachine->mode.data.target_mode.target.y);
    }
    else
    {
        // if in manual mode move the two carts, the whinch and the gripper if they has to
        Cart_tryMove(&clawMachine->cart_a);
        Cart_tryMove(&clawMachine->cart_b);

        Stepper_tryMove(&clawMachine->whinch);
        Servo_tryMove(&clawMachine->gripper);
    }
}
