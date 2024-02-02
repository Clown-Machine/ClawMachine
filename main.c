#include "include/ControllerSetup.h"
#include "include/InterruptHandler.h"
#include "include/ControllerFSM.h"
#include "msp.h"
#include <ti/devices/msp432p4xx/inc/msp.h>
#include <ti/devices/msp432p4xx/driverlib/driverlib.h>
#include <ti/devices/msp432p4xx/driverlib/adc14.h>
#include <stdio.h>


///-----------------------------------------------------------------------------------------------------------------------------
// cancel once you include controoller.h
///-----------------------------------------------------------------------------------------------------------------------------







///------------------------------------------------------------------------------------------------------------------------------

int main(void)
 {
    //uint16_t i = 0;

    WDT_A_holdTimer();    // stop watchdog timer
    /* initialize timers */
    hwInit();
    timerInit();

    /* initialize buttons */
    buttonInit();

    /* initialize LED */
    ledInit();

    /* initialize joystick */
    joystickInit();


    while(1){
        PCM_gotoLPM0();
        Controller();
    }
}
