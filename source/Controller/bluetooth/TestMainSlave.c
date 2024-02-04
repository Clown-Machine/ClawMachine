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

    # if DEBUG

    while (1)
    {
        __sleep();
     }
    #endif

    return 0;
}

////UART handler for EUSCIA2
//void EUSCIA2_IRQHandler(void)
//{
//   uint8_t c;
//   uint32_t status = MAP_UART_getEnabledInterruptStatus(EUSCI_A2_BASE);
//   MAP_UART_clearInterruptFlag(EUSCI_A2_BASE, status);
//
//   if(status & EUSCI_A_UART_RECEIVE_INTERRUPT)
//   {
//       c = MAP_UART_receiveData(EUSCI_A2_BASE);
//
//       InterpretCommand(c, &clawMachine);
//       Interrupt_disableSleepOnIsrExit(); //
//   }
//}
