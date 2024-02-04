#include "config.h"

// timer settings for servo PWM
Timer_A_UpModeConfig servoTimerPWMConfig = {
       TIMER_A_CLOCKSOURCE_SMCLK,              // SMCLK = 24 MHz
       TIMER_A_CLOCKSOURCE_DIVIDER_12,         // SMCLK/12 = 2MHz
       40000,                                  // 20 ms tick period
       TIMER_A_TAIE_INTERRUPT_DISABLE,         // Disable Timer interrupt
       TIMER_A_CCIE_CCR0_INTERRUPT_DISABLE,    // Disable CCR0 interrupt
       TIMER_A_DO_CLEAR                        // Clear value
};

// function to set a pin to a pecific value using a parameter
void GPIO_setOutputOnPin(uint_fast8_t selectedPort, uint_fast16_t selectedPins, PinValue_t value) {
    switch(value) {
        case HIGH:
            GPIO_setOutputHighOnPin(selectedPort, selectedPins);
            break;
        case LOW:
            GPIO_setOutputLowOnPin(selectedPort, selectedPins);
            break;
        case TOGGLE:
            GPIO_toggleOutputOnPin(selectedPort, selectedPins);
            break;
        default:
            break;
    }
}
