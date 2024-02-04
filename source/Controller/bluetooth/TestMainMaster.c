#include <ti/devices/msp432p4xx/driverlib/driverlib.h>
#include <stdio.h>
#include <BlueTooth/BluetoothLibrary/BlueLib.h>
#include "msp.h"
#define DEBUG 1

int main()
{

    WDT_A_holdTimer();

        BlueToothHardwareInit();

        MAP_Interrupt_enableMaster();

        Settings();

        #if DEBUG
        uint8_t vel = 65;

        //to efficiently test each command, send one at a time with debug
        moveXBackwards(vel);
        moveYBackwards(vel);
        moveXForward(vel);
        moveYForward(vel);

        moveGripperUp(vel);
        moveGripperDown(vel);

        OpenGripper(vel);
        CloseGripper(vel);

        GoToTarget(0);
        GoToTarget(1);
        GoToTarget(2);
        GoToTarget(3);

        SaveTarget(0);
        SaveTarget(1);
        SaveTarget(2);
        SaveTarget(3);
        #endif

    return 0;
}
