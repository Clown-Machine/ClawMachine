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
    //uint32_t i = 0;
    status = GPIO_getEnabledInterruptStatus(GPIO_PORT_P5);

    if(status & GPIO_PIN1)
    {
        event = SW1_PRESSED;
        printf("SW1_PRESSED\n");
    }
    GPIO_clearInterruptFlag(GPIO_PORT_P5, status);
}

// button 3
void PORT4_IRQHandler(){
    uint32_t status;
    //uint32_t i = 0;
    status = GPIO_getEnabledInterruptStatus(GPIO_PORT_P4);

    if(status & GPIO_PIN1)
    {
        /*GPIO_toggleOutputOnPin(GPIO_PORT_P2, GPIO_PIN2);
        for(i = 0; i < 100000; i++);
        GPIO_toggleOutputOnPin(GPIO_PORT_P2, GPIO_PIN2);*/
        event = SW3_PRESSED;
        printf("SW3_PRESSED\n");
    }
    GPIO_clearInterruptFlag(GPIO_PORT_P4, status);
}

// button 2
void PORT3_IRQHandler(){
    uint32_t status;
    //uint32_t i = 0;
    status = GPIO_getEnabledInterruptStatus(GPIO_PORT_P3);

    if(status & GPIO_PIN5)
    {
        /*GPIO_toggleOutputOnPin(GPIO_PORT_P2, GPIO_PIN1);
        for(i = 0; i < 100000; i++);
        GPIO_toggleOutputOnPin(GPIO_PORT_P2, GPIO_PIN1);*/
        event = SW2_PRESSED;
        printf("SW2_PRESSED\n");
    }
    GPIO_clearInterruptFlag(GPIO_PORT_P3, status);
}

void TA1_N_IRQHandler(){
    /* clear interrupt flag */
    Timer_A_clearInterruptFlag(TIMER_A1_BASE);
    /* toggle conversion trigger - start joystick sampling */
    ADC14_toggleConversionTrigger();
}
