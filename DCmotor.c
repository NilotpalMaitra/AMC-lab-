#include <stdint.h>
#include "inc/tm4c123gh6pm.h"

void delayMs(int n);

int main(void)
{
    // Enable clock to GPIOF at the Clock Gating Control Register
    SYSCTL_RCGCGPIO_R |= SYSCTL_RCGCGPIO_R5;  // GPIOF clock enable
    while ((SYSCTL_PRGPIO_R & SYSCTL_PRGPIO_R5) == 0);  // Wait for GPIOF to be ready

    // Set PF2 and PF3 as output (binary: 0x0E -> PF2 and PF3 are output)
    GPIO_PORTF_DIR_R = 0x0E;  // PF2 and PF3 are output, PF0 and PF1 are input
    GPIO_PORTF_DEN_R = 0x0E;  // Enable digital functionality on PF2 and PF3

    // Optionally, set pull-up resistors for PF0 and PF4 (buttons) if used
    // GPIO_PORTF_PUR_R = 0x11;  // Enable pull-up resistors on PF0 and PF4 if you have buttons

    while(1)
    {
        // Set PF3 high (turn on blue LED)
        GPIO_PORTF_DATA_R = 0x08;  // PF3 = 1, PF2 = 0 (Blue LED on)
        delayMs(500);  // Delay for 500 ms

        // Set PF3 low (turn off blue LED)
        GPIO_PORTF_DATA_R = 0x00;  // PF3 = 0, PF2 = 0 (Blue LED off)
        delayMs(500);  // Delay for 500 ms
    }
}

// Delay function that approximates a 1 ms delay (16 MHz CPU clock)
void delayMs(int n)
{
    int i, j;
    for(i = 0; i < n; i++) {
        for(j = 0; j < 3180; j++) {}  // Do nothing for 1 ms
    }
}
