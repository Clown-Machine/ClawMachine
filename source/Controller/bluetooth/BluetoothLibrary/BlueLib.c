#if CONTROLLER
#include <BlueTooth/BluetoothLibrary/BitOperations.h>
#endif
#if MOTORS
#include "./claw_machine.h"
#endif

#include <bluetooth/BluetoothLibrary/BlueLib.h>
#include <stdio.h>
#include <ti/devices/msp432p4xx/driverlib/driverlib.h>

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

void sendToBluetooh(uint8_t buffer)
{
    MAP_UART_transmitData(EUSCI_A2_BASE, buffer);
}

void bluetoothHardwareInit()
{
    MAP_GPIO_setAsPeripheralModuleFunctionInputPin(GPIO_PORT_P3, GPIO_PIN2 | GPIO_PIN3, GPIO_PRIMARY_MODULE_FUNCTION);
    MAP_UART_initModule(EUSCI_A2_BASE, &UART2Config);
    MAP_UART_enableModule(EUSCI_A2_BASE);
    MAP_UART_enableInterrupt(EUSCI_A2_BASE, EUSCI_A_UART_RECEIVE_INTERRUPT);
    MAP_Interrupt_enableInterrupt(INT_EUSCIA2);
}

void motorSideSettings()
{
    FlashCtl_setWaitState(FLASH_BANK0, 1);
    FlashCtl_setWaitState(FLASH_BANK1, 1);
    PCM_setCoreVoltageLevel(PCM_VCORE1);
    CS_setDCOCenteredFrequency(CS_DCO_FREQUENCY_24);
    Interrupt_enableSleepOnIsrExit();
}

#if MOTORS
void interpretCommand(uint8_t value, ClawMachine_t *clawMachine)
{

    uint8_t mode = ((value & 1) == 1 ? 1 : 0);

    if (mode == MANUAL)
    {
        interpretMovement(value, clawMachine);
    }
    else if (mode == AUTOMATIC)
    {
        interpretTarget(value, clawMachine);
    }
}

void interpretMovement(uint8_t value, ClawMachine_t *clawMachine)
{
    uint8_t mask12 = 6; // second and third bit are one, the others zero

    uint8_t status = ((value & mask12) >> 1);                   // only second and third bit are set and then shift of one
    uint8_t direction = ((value & (1 << 3)) >> 3 == 1 ? 1 : 0); // get fourth bit (and shift to first position)
    int8_t velocity = (value >> 4);                             // shift to have velocity bits only

    if (status == HORIZONTALX)
    {
        if (direction == FORWARDS)
        {
#if DEBUG
            printf("move on x forward with velocity %u\n", velocity);
#endif

            Claw_setXSpeed(clawMachine, velocity);
        }
        else if (direction == BACKWARDS)
        {

#if DEBUG
            printf("move on x backwards with velocity %u\n", velocity);
#endif

            Claw_setXSpeed(clawMachine, -velocity);
        }
    }
    else if (status == HORIZONTALY)
    {
        if (direction == FORWARDS)
        {
#if DEBUG
            printf("move on y forward with velocity %u\n", velocity);
#endif

            Claw_setYSpeed(clawMachine, velocity);
        }
        else if (direction == BACKWARDS)
        {
#if DEBUG
            printf("move on y backwards with velocity %u\n", velocity);
#endif

            Claw_setYSpeed(clawMachine, -velocity);
        }
    }
    else if (status == VERTICAL)
    {
        if (direction == FORWARDS)
        {
#if DEBUG
            printf("move on z up with velocity %u\n", velocity);
#endif

            Claw_setZSpeed(clawMachine, -velocity);
        }
        else if (direction == BACKWARDS)
        {
#if DEBUG
            printf("move on z down with velocity %u\n", velocity);
#endif

            Claw_setZSpeed(clawMachine, velocity);
        }
    }
    else if (status == GRIPPER)
    {
        if (direction == FORWARDS)
        {
#if DEBUG
            printf("open gripper with velocity\n", velocity);
#endif

            Claw_setGripperSpeed(clawMachine, velocity);
        }
        else if (direction == BACKWARDS)
        {
#if DEBUG
            printf("close gripper with velocity\n", velocity);
#endif

            Claw_setGripperSpeed(clawMachine, -velocity);
        }
    }
}

void interpretTarget(uint8_t value, ClawMachine_t *clawMachine)
{
    uint8_t goOrSave = ((value & (1 << 1)) >> 1 == 1 ? 1 : 0);
    uint8_t target = value >> 2;

    if (goOrSave == GO)
    {
#if DEBUG
        printf("go to target %u\n", target);
#endif

        Claw_setTargetMode(clawMachine, target);
    }
    else if (goOrSave == SAVE)
    {
#if DEBUG
        printf("save target %u\n", target);
#endif

        Claw_updateTargetValue(clawMachine, target);
    }
}

#elif CONTROLLER
void moveXForward(int velocity)
{
    uint8_t value = 0;

    value = encodeVelocity(velocity, value);

    sendToBluetooh(value);
}
void moveXBackwards(int velocity)
{
    uint8_t value = 0;

    value = SetNbitToOne(value, 3);
    value = encodeVelocity(velocity, value);

    sendToBluetooh(value);
}
void moveYForward(int velocity)
{
    uint8_t value = 0;

    value = SetNbitToOne(value, 2);
    value = encodeVelocity(velocity, value);

    sendToBluetooh(value);
}
void moveYBackwards(int velocity)
{
    uint8_t value = 0;

    value = SetNbitToOne(value, 2);
    value = SetNbitToOne(value, 3);
    value = encodeVelocity(velocity, value);

    sendToBluetooh(value);
}

void moveGripperUp(int velocity)
{
    uint8_t value = 0;

    value = SetNbitToOne(value, 1);
    value = encodeVelocity(velocity, value);

    sendToBluetooh(value);
}
void moveGripperDown(int velocity)
{
    uint8_t value = 0;

    value = SetNbitToOne(value, 1);
    value = SetNbitToOne(value, 3);
    value = encodeVelocity(velocity, value);

    sendToBluetooh(value);
}

void openGripper(int velocity)
{
    uint8_t value = 0;

    value = SetNbitToOne(value, 1);
    value = SetNbitToOne(value, 2);
    value = encodeVelocity(velocity, value);

    sendToBluetooh(value);
}
void closeGripper(int velocity)
{
    uint8_t value = 0;

    value = SetNbitToOne(value, 1);
    value = SetNbitToOne(value, 2);
    value = SetNbitToOne(value, 3);
    value = encodeVelocity(velocity, value);

    sendToBluetooh(value);
}

void goToTarget(int target)
{
    if (target <= 3 && target >= 0)
    { // we have 4 targets (from target 0 to 3)

        uint8_t value = 0;

        value = SetNbitToOne(value, 0);
        value = SetNbitToOne(value, 1);

        value = encodeTarget(target, value);

        sendToBluetooh(value);
    }
}

void saveTarget(int target) // we have 4 targets (from target 0 to 3)
{
    if (target <= 3 && target >= 0)
    {
        uint8_t value = 0;

        value = SetNbitToOne(value, 0);
        value = encodeTarget(target, value);

        sendToBluetooh(value);
    }
}
#endif
