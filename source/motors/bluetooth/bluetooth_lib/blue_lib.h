#ifndef BLUE_LIB
#define BLUE_LIB

#include <stdio.h>
#include <ti/devices/msp432p4xx/driverlib/driverlib.h>
#define MOTORS 1
#define CONTROLLER 0
#define DEBUG 0

#if CONTROLLER
#include "bit_operations.h"
#endif
#if MOTORS
#include "../../claw_machine_driver/claw_machine.h"
#endif

/*wrapper for low-level function that writes on UART
 * Parameters: an uint8_t, the value that has to be transmitted
 */
void sendToBluetooh(uint8_t buffer);
// wrapper low-level functions that initializes necessary hardware for UART
void bluetoothHardwareInit();
void motorSideSettings();

#if MOTORS

/*function that interprets the received commands
 * Parameters: values to be interpreted into a command
 */
void interpretCommand(uint8_t buffer, ClawMachine_t *clawMachine);

/*functions called by InterpretCommand() depending on what mode the machine is
 * Parameters: values to be interpreted into a command
 */
void interpretMovement(uint8_t value, ClawMachine_t *clawMachine);
void interpretTarget(uint8_t value, ClawMachine_t *clawMachine);

#elif CONTROLLER
/*functions used for encoding and sending commands over UART*/
/* Parameters: velocity of the desired movement*/
void moveXForward(int velocity);
void moveXBackwards(int velocity);
void moveYForward(int velocity);
void moveYBackwards(int velocity);

void moveGripperUp(int velocity);
void moveGripperDown(int velocity);

void openGripper(int velocity);
void closeGripper(int velocity);

/* Parameters: target of the desired movement*/
void goToTarget(int target);
void saveTarget(int target);
#endif

#endif

//////////////////////////////////////////////
/*DATA ENCODING

 ____MOVEMENT: first bit: 0 (=movement)

Second/Third BIT: status and direction
status horizontal:      0 0 axis x
                        0 1 axis y

status vertical:        1 0 up/down
                        1 1 gripper

Fourth BIT:
in status horizontal=>  0 FORWARDS
                        1 backwards

in status vertical =>   up/down => 0 = up (forwards)
                        up/down => 1 = down (backwards)

                        gripper => 0 = open (forwards)
                        gripper => 1 = close (backwards)

Others BITs: velocity (all zeros = not moving)


___TARGET: first bit: 1

Second bit 0 : overwrite target
target represented by the remaining bits

Second bit 1: go to target
target represented by the remaining bits

 */
//////////////////////////////////////////////////////////

