#include <stdint.h>
#include "inc/tm4c123gh6pm.h"

int main(void)
{
    unsigned int value;

    // Enable clock for GPIOF
    SYSCTL_RCGCGPIO_R |= 0x20;  // Clock for PORTF (bit 5)

    // Wait for the GPIOF module to be ready
    while ((SYSCTL_PRGPIO_R & 0x20) == 0) {};

    // Set pins 1, 2, and 3 of GPIOF as output (LEDs)
    GPIO_PORTF_DIR_R = 0x0E;   // PF1, PF2, PF3 as output (LEDs)
    
    // Set pin 4 (switch) of GPIOF as input, enable pull-up resistor
    GPIO_PORTF_DIR_R &= ~0x10;  // PF4 as input
    GPIO_PORTF_DEN_R = 0x1F;    // Enable digital functions on all pins (PF0 to PF4)
    GPIO_PORTF_PUR_R = 0x10;    // Enable pull-up resistor on PF4 (switch)

    while(1)
    {
        // Read the value of the GPIOF data register
        value = GPIO_PORTF_DATA_R;

        // Check if the switch (PF4) is pressed (low active)
        if ((value & 0x10) == 0)  // PF4 is pressed (active low)
        {
            // If switch is pressed, turn on the red LED (PF1), and turn off others
            GPIO_PORTF_DATA_R = 0x02;  // Only PF1 (red LED) is on
        }
        else
        {
            // If switch is not pressed, turn off all LEDs
            GPIO_PORTF_DATA_R = 0x00;  // All LEDs off
        }
    }
}
