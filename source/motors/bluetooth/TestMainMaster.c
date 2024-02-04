#include <ti/devices/msp432p4xx/driverlib/driverlib.h>
#include <stdio.h>
#include "bluetooth_lib/blue_lib.h"
#include "bluetooth_lib/bit_operations.h"
#include "hardware/UART_Driver.h"
#include "msp.h"

//int main()
//{
//
//    WDT_A_holdTimer();
//
//    BlueToothHardwareInit();
//
//    MAP_Interrupt_enableMaster();
//
//    Settings();
//
//    CheckUART();
//
//    printf("Hi\n");
//    uint8_t  data[1];
//    data[0] = 1;
//
//    uint8_t vel = 65;
//
//    //UART_Write(EUSCI_A2_BASE, data, 1);
//
//    moveXBackwards(vel);
////    moveYBackwards(vel);
////    moveXForward(vel);
////    moveYForward(vel);
////
////    moveGripperUp(vel);
////    moveGripperDown(vel);
////
////    OpenGripper(vel);
////    CloseGripper(vel);
////
////    GoToTarget(3);
////    SaveTarget(4);
//
//
//    return 0;
//}
