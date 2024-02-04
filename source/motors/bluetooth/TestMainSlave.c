#include <ti/devices/msp432p4xx/driverlib/driverlib.h>
#include <stdio.h>
#include "bluetooth_lib/blue_lib.h"


#include "msp.h"

#define DEBUG 1

ClawMachine_t clawMachine;

int32_t direction = 2000;
int32_t direction_b = 2000;

void init();

int main()
{
    WDT_A_holdTimer();

    bluetoothHardwareInit();

    MAP_Interrupt_enableMaster();

    motorSideSettings();

    # if DEBUG

    while (1)
    {
        __sleep();
     }

    #endif

    return 0;
}

//UART handler for EUSCIA2
void EUSCIA2_IRQHandler(void)
{
   uint8_t c;
   uint32_t status = MAP_UART_getEnabledInterruptStatus(EUSCI_A2_BASE);
   MAP_UART_clearInterruptFlag(EUSCI_A2_BASE, status);

   if(status & EUSCI_A_UART_RECEIVE_INTERRUPT)
   {
       c = MAP_UART_receiveData(EUSCI_A2_BASE);

       #if DEBUG
       printf("received data: %u\n", c);
       #endif

       interpretCommand(c, &clawMachine);
       Interrupt_disableSleepOnIsrExit();
   }
}
