#include <ti/devices/msp432p4xx/driverlib/driverlib.h>
#include <stdio.h>
#include "bluetooth_lib/blue_lib.h"
#include "bluetooth_lib/bit_operations.h"
#include "hardware/UART_Driver.h"
#include "msp.h"

#define DEBUG 1

//int main()
//{
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
//    # if DEBUG
//    uint8_t data[1];
//    while (1)
//    {
//        ReadFromBlueTooth(data);
//
//        // InterpretCommand(data[0]); ???
//    }
//    #endif
//
//    return 0;
//}
