#include "include/ControllerSetup.h"
#include "include/InterruptHandler.h"
#include "include/ControllerFSM.h"
#include "msp.h"
#include <ti/devices/msp432p4xx/inc/msp.h>
#include <ti/devices/msp432p4xx/driverlib/driverlib.h>
#include <ti/devices/msp432p4xx/driverlib/adc14.h>
#include <stdio.h>
#include "Graphics/default_screens.h"
#include "bluetooth/BluetoothLibrary/BlueLib.h"

int main(void)
{
    WDT_A_holdTimer(); // stop watchdog timer
    /* initialize GUI */
    _screenInit();

    /* initialize timers */
    /* initialize buttons */
    /* initialize joystick */
    controllerInit();

    /*initialzie Bluetooth */
    bluetoothHardwareInit();

    screenBluetoothPairing();
    while (1)
    {
        // PCM_gotoLPM0();
        // controller state machine
        Controller();
    }
}
