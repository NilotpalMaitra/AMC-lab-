#include <stdint.h>
#include "inc/tm4c123gh6pm.h"

void delayMs(int n);

int main(void)
{
    // Enable clock to GPIOF, GPIOB, and GPIOC
    SYSCTL_RCGCGPIO_R |= 0x20;  // Enable clock for GPIOF (bit 5)
    SYSCTL_RCGCGPIO_R |= 0x02;  // Enable clock for GPIOB (bit 1)
    SYSCTL_RCGCGPIO_R |= 0x04;  // Enable clock for GPIOC (bit 2)

    // Configure PF2, PF3, PB3, and PC4 as outputs
    GPIO_PORTF_DIR_R = 0x0C;  // PF2 and PF3 as output
    GPIO_PORTB_DIR_R = 0x08;  // PB3 as output
    GPIO_PORTC_DIR_R = 0x10;  // PC4 as output

    // Enable digital functions for PF2, PF3, PB3, and PC4
    GPIO_PORTF_DEN_R = 0x0C;  // PF2 and PF3 as digital
    GPIO_PORTB_DEN_R = 0x08;  // PB3 as digital
    GPIO_PORTC_DEN_R = 0x10;  // PC4 as digital

    while(1)
    {
        // Set PF2 (red LED) high
        GPIO_PORTF_DATA_R = 0x04;  // PF2 = 1
        delayMs(500);  // Delay for 500 ms
        GPIO_PORTF_DATA_R = 0;     // PF2 = 0 (turn off)
        delayMs(500);  // Delay for 500 ms

        // Set PF3 (blue LED) high
        GPIO_PORTF_DATA_R = 0x08;  // PF3 = 1
        delayMs(500);  // Delay for 500 ms
        GPIO_PORTF_DATA_R = 0;     // PF3 = 0 (turn off)
        delayMs(500);  // Delay for 500 ms

        // Set PB3 (green LED) high
        GPIO_PORTB_DATA_R = 0x08;  // PB3 = 1
        delayMs(500);  // Delay for 500 ms
        GPIO_PORTB_DATA_R = 0;     // PB3 = 0 (turn off)
        delayMs(500);  // Delay for 500 ms

        // Set PC4 high
        GPIO_PORTC_DATA_R = 0x10;  // PC4 = 1
        delayMs(500);  // Delay for 500 ms
        GPIO_PORTC_DATA_R = 0;     // PC4 = 0 (turn off)
        delayMs(500);  // Delay for 500 ms
    }
}

// delay n milliseconds (16 MHz CPU clock)
void delayMs(int n)
{
    int i, j;
    for(i = 0; i < n; i++)
        for(j = 0; j < 3180; j++) {}  // Adjusted for ~1 ms delay
}
