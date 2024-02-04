#include "include/InterruptHandler.h"
#include "msp.h"

uint16_t resultsBuffer[2] = {8000, 8000};
extern Event_t event;

// joystick
void ADC14_IRQHandler()
{
    uint64_t status;
    status = ADC14_getEnabledInterruptStatus();

    if(status & ADC_INT1)
    {
        /* Store ADC14 conversion results */
        resultsBuffer[0] = ADC14_getResult(ADC_MEM0);
        resultsBuffer[1] = ADC14_getResult(ADC_MEM1);
    }
    ADC14_clearInterruptFlag(status);
}

// button 1
void PORT5_IRQHandler(){
    uint32_t status;
    status = GPIO_getEnabledInterruptStatus(GPIO_PORT_P5);

    if(status & GPIO_PIN1)
    {
        event = SW1_PRESSED;
    }
    GPIO_clearInterruptFlag(GPIO_PORT_P5, status);
}

// button 3
void PORT4_IRQHandler(){
    uint32_t status;
    status = GPIO_getEnabledInterruptStatus(GPIO_PORT_P4);

    if(status & GPIO_PIN1)
    {
        event = SW3_PRESSED;
    }
    GPIO_clearInterruptFlag(GPIO_PORT_P4, status);
}

// button 2
void PORT3_IRQHandler(){
    uint32_t status;
    status = GPIO_getEnabledInterruptStatus(GPIO_PORT_P3);

    if(status & GPIO_PIN5)
    {
        event = SW2_PRESSED;
    }
    GPIO_clearInterruptFlag(GPIO_PORT_P3, status);
}

void TA1_N_IRQHandler(){
    /* clear interrupt flag */
    Timer_A_clearInterruptFlag(TIMER_A1_BASE);
    /* toggle conversion trigger - start joystick sampling */
    ADC14_toggleConversionTrigger();
}
