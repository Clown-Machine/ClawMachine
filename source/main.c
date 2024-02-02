#include "stdlib.h"
#include "stdio.h"
#include "BlueTooth/BluetoothLib/BlueLib.h"

#include "msp.h"
#include <ti/devices/msp432p4xx/driverlib/driverlib.h>

#include "global.h"
#include "stepper.h"
#include "cart.h"
#include "claw_machine.h"
#include "config.h"

// statics

ClawMachine_t clawMachine;

int32_t direction = 2000;
int32_t direction_b = 2000;

void init();

void main(void)
{
    WDT_A_holdTimer();

    // bluetooth initialization
    BlueToothHardwareInit();

    //MAP_Interrupt_enableMaster();

    //Settings();
    ///////////////

    init();

    printf("start\n");

    while (1)
    {

        //__sleep();

        uint8_t command[1];
            ReadFromBlueTooth(command);

            //printf("commando: %u\n",command[0]);
            InterpretCommand(command[0], &clawMachine);


    }
}

void configureMotorsTimer_UpMode()
{
    Timer_A_configureUpMode(TIMER_A1_BASE, &timerConfig);

    Interrupt_enableSleepOnIsrExit();
    Interrupt_enableInterrupt(INT_TA1_0);

    Timer_A_startCounter(TIMER_A1_BASE, TIMER_A_UP_MODE);
}

void configureMainLoopTimer_ContinuoiusMode()
{
    CS_setReferenceOscillatorFrequency(CS_REFO_32KHZ);
    CS_initClockSignal(CS_ACLK, CS_REFOCLK_SELECT, CS_CLOCK_DIVIDER_1);

    Timer_A_configureContinuousMode(TIMER_A0_BASE, &mainLoopTimerConfig);

    Interrupt_enableSleepOnIsrExit();
    Interrupt_enableInterrupt(INT_TA0_N);

    Timer_A_startCounter(TIMER_A0_BASE, TIMER_A_CONTINUOUS_MODE);
}

void init()
{
    Cart_t cart_a = Cart_INIT(
        Stepper_INIT(CART_A_DX_IN1, CART_A_DX_IN2, CART_A_DX_IN3, CART_A_DX_IN4),
        Stepper_INIT(CART_A_SX_IN1, CART_A_SX_IN2, CART_A_SX_IN3, CART_A_SX_IN4));

    Cart_t cart_b = Cart_INIT(
        Stepper_INIT(CART_B_DX_IN1, CART_B_DX_IN2, CART_B_DX_IN3, CART_B_DX_IN4),
        Stepper_INIT(CART_B_SX_IN1, CART_B_SX_IN2, CART_B_SX_IN3, CART_B_SX_IN4));

    Stepper_t whinch = Stepper_INIT(WHINCH_IN1, WHINCH_IN2, WHINCH_IN3, WHINCH_IN4);

    clawMachine = Claw_INIT(cart_a, cart_b, whinch);

    configureMotorsTimer_UpMode();
    configureMainLoopTimer_ContinuoiusMode();

    Claw_setXSpeed(&clawMachine, 0);
    Claw_setYSpeed(&clawMachine, 0);
    Claw_setZSpeed(&clawMachine, 0);
    Claw_setGripperSpeed(&clawMachine, 0);

    // Enabling MASTER interrupts
    Interrupt_enableMaster();
}

// stepper motor control loop
void TA1_0_IRQHandler(void)
{
    Timer_A_clearCaptureCompareInterrupt(TIMER_A1_BASE, TIMER_A_CAPTURECOMPARE_REGISTER_0);

//    uint8_t command[1];
//    ReadFromBlueTooth(command);
//
//    //printf("commando: %u\n",command[0]);
//    InterpretCommand(command[0], &clawMachine);

    Claw_tryMove(&clawMachine);
}

// main loop (bluetooth reading)
int counter = 0;
void TA0_N_IRQHandler(void)
{
    Timer_A_clearInterruptFlag(TIMER_A0_BASE);

    // uint8_t command[1];
    // ReadFromBlueTooth(command);
    // InterpretCommand(command[0], clawMachine);

    // Position_t a =  {1000, 1000};
    // Position_t b =  {1000, 3000};
    // Position_t c =  {3000, 3000};
    // Position_t d =  {3000, 1000};

    // switch (counter % 9) {
    // case 0:
    //     Claw_setTargetMode(&clawMachine, a);
    //     break;
    // case 1:
    //     Claw_setTargetMode(&clawMachine, b);
    //     break;
    // case 2:
    //     Claw_setTargetMode(&clawMachine, c);
    //     break;
    // case 3:
    //     Claw_setTargetMode(&clawMachine, d);
    //     break;
    // case 4:
    //     Claw_setManualMode(&clawMachine, 0, 0, 100, 0);
    //     break;
    // case 5:
    //     Claw_setManualMode(&clawMachine, 0, 0, -100, 0);
    //     break;
    // case 6:
    //     Claw_setManualMode(&clawMachine, 0, 0, 0, 50);
    //     break;
    // case 7:
    //     Claw_setManualMode(&clawMachine, 0, 0, 0, -50);
    //     break;
    // case 8:

    //     break;
    // }
    counter++;
}
