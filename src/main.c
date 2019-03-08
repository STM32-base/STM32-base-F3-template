#include "stm32f3xx.h"

// Quick and dirty delay
static void delay (unsigned int time) {
    for (unsigned int i = 0; i < time; i++)
        for (volatile unsigned int j = 0; j < 2000; j++);
}

int main (void) {
    // Turn on the GPIOC peripheral
    RCC->AHBENR |= RCC_AHBENR_GPIOCEN;

    // Put pin 13 in general purpose mode
    GPIOC->MODER  |= GPIO_MODER_MODER13_0;

    while (1) {
        // Reset the state of pin 13 to output low
        GPIOC->BSRR = GPIO_BSRR_BR_13;

        delay(500);

        // Set the state of pin 13 to output high
        GPIOC->BSRR = GPIO_BSRR_BS_13;

        delay(500);
    }

    // Return 0 to satisfy compiler
    return 0;
}
