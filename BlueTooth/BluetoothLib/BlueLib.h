#ifndef BLUE_LIB
#define BLUE_LIB

#include <stdio.h>
#include <ti/devices/msp432p4xx/driverlib/driverlib.h>
#include "./BlueTooth/Hardware/UART_Driver.h"
#include "./claw_machine.h"

/*wrapper for driver function that reads UART buffer
Parameters: array of uint8_t containing data to be sent
*/
int ReadFromBlueTooth(uint8_t *buffer);

/*wrapper for driver function that writes on UART
 * Parameters: buffer of uint8_t in which data will be written
 */
void SendToBlueTooth(uint8_t buffer);

// wrapper for driver function that initializes necessary hardware for UART
void BlueToothHardwareInit();

//
void Settings();

/*function that interprets the received commands
 * Parameters: values to be interpreted into a command
 */
void InterpretCommand(uint8_t buffer, ClawMachine_t *clawMachine);

/*functions called by InterpretCommand() depending on what mode we are in
 * Parameters: values to be interpreted into a command
 */
void interpretManual(uint8_t value, ClawMachine_t *clawMachine);
void interpretAutomatic(uint8_t value, ClawMachine_t *clawMachine);

/*functions that encode and send commands over bluetooth*/

/* Parameters: velocity of the desired movement*/
void moveXForward(int velocity);
void moveXBackwards(int velocity);
void moveYForward(int velocity);
void moveYBackwards(int velocity);

void moveGripperUp(int velocity);
void moveGripperDown(int velocity);

void OpenGripper(int velocity);
void CloseGripper(int velocity);

/* Parameters: target of the desired movement*/
void GoToTarget(int target, ClawMachine_t *clawMachine);

void SaveTarget();
#endif
