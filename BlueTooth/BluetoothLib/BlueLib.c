#include <stdio.h>

#include <ti/devices/msp432p4xx/driverlib/driverlib.h>
#include "./BlueTooth/Hardware/UART_Driver.h"
#include "BitOperations.h"
#include "./claw_machine.h"
#include "BlueLib.h"

#define BUFFER_SIZE 1
#define MANUAL 0
#define AUTOMATIC 1
#define HORIZONTALX 0
#define HORIZONTALY 2
#define VERTICAL 1
#define GRIPPER 3
#define FORWARDS 0
#define BACKWARDS 1
#define GO 1
#define SAVE 0




// object for UART configuration parameters
const eUSCI_UART_ConfigV1 UART2Config =
    {
        EUSCI_A_UART_CLOCKSOURCE_SMCLK,
        156,
        4,
        0,
        EUSCI_A_UART_NO_PARITY,
        EUSCI_A_UART_LSB_FIRST,
        EUSCI_A_UART_ONE_STOP_BIT,
        EUSCI_A_UART_MODE,
        EUSCI_A_UART_OVERSAMPLING_BAUDRATE_GENERATION};

int ReadFromBlueTooth(uint8_t *buffer)
{
    return UART_Read(EUSCI_A2_BASE, buffer, BUFFER_SIZE);
}

void SendToBlueTooth(uint8_t buffer)
{
    uint8_t data[1];
    data[0] = buffer;
    UART_Write(EUSCI_A2_BASE, data, BUFFER_SIZE);
}

void BlueToothHardwareInit()
{
    UART_Init(EUSCI_A2_BASE, UART2Config);
}

void Settings()
{
    FlashCtl_setWaitState(FLASH_BANK0, 1);
    FlashCtl_setWaitState(FLASH_BANK1, 1);
    PCM_setCoreVoltageLevel(PCM_VCORE1);
    CS_setDCOCenteredFrequency(CS_DCO_FREQUENCY_24);
    Interrupt_enableSleepOnIsrExit();
}

//////////////////////////////////////////////
/*DATA CODIFICATION

 ____MANUAL: first bit: 0 (=movement)

Second/Third BIT: status and direction
status horizontal: 0 0 axis x
                   0 1 axis y

status vertical: 1 0 up/down
                 1 1 gripper

Fourth BIT:
in status horizontal=>  0 FORWARDS
                        1 backwards

in status vertical =>  up/down => 0 = up (forwards)
                       up/down => 1 = down (backwards)

                       gripper => 0 = open (forwards)
                       gripper => 1 = close (backwards)

Others BITs: velocity
all zeros = not moving
otherwise convert number


___AUTOMATIC: first bit: 1

Second bit 0 : overwrite target
target represented by the remaining bits

Second bit 1: go to target
target represented by the remaining bits

 */

//////////////////////////////////////////////////////////
void InterpretCommand(uint8_t value, ClawMachine_t *clawMachine)
{

    uint8_t mode = ((value & 1) == 1 ? 1 : 0);

    if (mode == MANUAL)
    {
        interpretManual(value, clawMachine);
    }
    else if (mode == AUTOMATIC)
    {
        interpretAutomatic(value, clawMachine);
    }
}

void interpretManual(uint8_t value, ClawMachine_t *clawMachine)
{
    uint8_t mask12 = 6; // second and third bit are one, the others zero

    uint8_t status = ((value & mask12) >> 1);                   // only second and third bit are set and then shift of one
    uint8_t direction = ((value & (1 << 3)) >> 3 == 1 ? 1 : 0); // get fourth bit (and shift to first position)
    int8_t velocity = (value >> 4);                             // shift to have velocity bits only

    if (status == HORIZONTALX)
    {
        if (direction == FORWARDS)
        {
            // move on axis x forward with velocity
            printf("move on x fw with velocity %u\n", velocity);

            Claw_setXSpeed(clawMachine, velocity);
        }
        else if (direction == BACKWARDS)
        {
            // move on axis X backward with velocity
            printf("move on x bk with velocity %u\n", velocity);

            Claw_setXSpeed(clawMachine, -velocity);
        }
    }
    else if (status == HORIZONTALY)
    {
        if (direction == FORWARDS)
        {
            // move on axis y forward with velocity
            printf("move on y fw with velocity %u\n", velocity);

            Claw_setYSpeed(clawMachine, velocity);
        }
        else if (direction == BACKWARDS)
        {
            // move on axis y backward with velocity
            printf("move on y bk with velocity %u\n", velocity);

            Claw_setYSpeed(clawMachine, -velocity);
        }
    }
    else if (status == VERTICAL)
    {
        if (direction == FORWARDS)
        {
            // move on axis Z up with velocity
            printf("move on z up with velocity %u\n", velocity);

            Claw_setZSpeed(clawMachine, velocity);
        }
        else if (direction == BACKWARDS)
        {
            // move on axis z down with velocity
            printf("move on z down with velocity %u\n", velocity);

            Claw_setZSpeed(clawMachine, -velocity);
        }
    }
    else if (status == GRIPPER)
    {
        if (direction == FORWARDS)
        {
            // open gripper
            printf("open\n");

            Claw_setGripperSpeed(clawMachine, velocity);
        }
        else if (direction == BACKWARDS)
        {
            // close gripper
            printf("close\n");

            Claw_setGripperSpeed(clawMachine, -velocity);
        }
    }
}

void interpretAutomatic(uint8_t value, ClawMachine_t *clawMachine)
{
    uint8_t goOrSave = ((value & (1 << 1)) >> 1 == 1 ? 1 : 0);
    uint8_t target = value >> 2;

//    if (goOrSave == GO)
//    {
//        printf("GO to target %u\n", target);
//
//        Position_t position = ; // funzione che ritorna position TODO
//        Claw_setTargetMode(clawMachine, position);
//    }
//    else if (goOrSave == SAVE)
//    {
//        printf("save target %u\n", target);
//
//        Position_t position = Claw_getCurrentPosition(clawMachine);

        // save position
//    }
}

/////////////////////////////////////////////

void moveXForward(int velocity)
{
    uint8_t value = 0;
    velocity = mapTo15(velocity);
    value = encodeVelocity(velocity, value);

    SendToBlueTooth(value);
}
void moveXBackwards(int velocity)
{
    uint8_t value = 0;
    velocity = mapTo15(velocity);

    value = SetNbitToOne(value, 3);
    value = encodeVelocity(velocity, value);

    SendToBlueTooth(value);
}
void moveYForward(int velocity)
{
    uint8_t value = 0;
    velocity = mapTo15(velocity);

    value = SetNbitToOne(value, 2);
    value = encodeVelocity(velocity, value);

    SendToBlueTooth(value);
}
void moveYBackwards(int velocity)
{
    uint8_t value = 0;
    velocity = mapTo15(velocity);

    value = SetNbitToOne(value, 2);
    value = SetNbitToOne(value, 3);
    value = encodeVelocity(velocity, value);

    SendToBlueTooth(value);
}

void moveGripperUp(int velocity)
{
    uint8_t value = 0;
    velocity = mapTo15(velocity);

    value = SetNbitToOne(value, 1);
    value = encodeVelocity(velocity, value);

    SendToBlueTooth(value);
}
void moveGripperDown(int velocity)
{
    uint8_t value = 0;
    velocity = mapTo15(velocity);

    value = SetNbitToOne(value, 1);
    value = SetNbitToOne(value, 3);
    value = encodeVelocity(velocity, value);

    SendToBlueTooth(value);
}

void OpenGripper(int velocity)
{
    uint8_t value = 0;
    velocity = mapTo15(velocity);

    value = SetNbitToOne(value, 1);
    value = SetNbitToOne(value, 2);
    value = encodeVelocity(velocity, value);

    SendToBlueTooth(value);
}
void CloseGripper(int velocity)
{
    uint8_t value = 0;
    velocity = mapTo15(velocity);

    value = SetNbitToOne(value, 1);
    value = SetNbitToOne(value, 2);
    value = SetNbitToOne(value, 3);
    value = encodeVelocity(velocity, value);

    SendToBlueTooth(value);
}

void GoToTarget(int target, ClawMachine_t *clawMachine)
{ ////TARGET??????
  // uint8_t value = 0;

    // value = SetNbitToOne(value, 0);
    // value = SetNbitToOne(value, 1);

    // // transform position to int
    // value = encodeTarget(target, value);

    // SendToBlueTooth(value);
}

void SaveTarget(int target)
{
    // uint8_t value = 0;

    // value = SetNbitToOne(value, 0);
    // value = encodeTarget(target, value);

    // SendToBlueTooth(value);
}
