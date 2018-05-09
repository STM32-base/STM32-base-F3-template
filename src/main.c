#include "STM32F3xx.h"

// Quick and dirty delay
static void delay (unsigned int time) {
    for (unsigned int i = 0; i < time; i++)
        for (volatile unsigned int j = 0; j < 2000; j++);
}

int main (void) {
    // Turn on the GPIOC peripheral
    RCC->AHBENR |= RCC_AHBENR_GPIOCEN;

    // Put the pin in general purpose mode
    GPIOC->MODER  |= GPIO_MODER_MODER13_0;

    while (1) {
        // Reset the bit for port C13
        GPIOC->BSRR = GPIO_BSRR_BR_13;

        delay(500);

        // Set the bit for port C13
        GPIOC->BSRR = GPIO_BSRR_BS_13;

        delay(500);
    }
}
