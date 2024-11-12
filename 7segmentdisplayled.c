#include <stdint.h>
#include "inc/tm4c123gh6pm.h"

// Function Prototypes
void delayMs(int n);
void shift_out1(unsigned char str);

int main(void)
{
    unsigned int i;
    unsigned char a[4] = {0xFC, 0x3E, 0xFC, 0xB6};  // 7-segment data for digits (example values)

    // Enable Clock for Port E (GPIO Port E)
    SYSCTL_RCGCGPIO_R |= 0x10;  

    // Set Port E Pins 0 to 4 as output
    GPIO_PORTE_DIR_R = 0x1F;    // PE4, PE3, PE2, PE1, PE0 are output
    GPIO_PORTE_DEN_R = 0x1F;    // Digital Enable for PE4 to PE0

    // Main loop to shift data to the 7-segment display
    for(i = 3; i >= 0; i--)
    {
        shift_out1(a[i]);  // Shift out the segment data
        delayMs(1000);      // Delay 1 second (1000ms)
    }

    return 0;
}

// Shift-out function to send data to the shift register (7-segment display)
void shift_out1(unsigned char str)
{
    unsigned char j;
    for(j = 0; j < 8; j++)  // Loop through all 8 bits
    {
        // Clear data and clock pins before setting new values
        GPIO_PORTE_DATA_R &= ~0x1C;  // Clear PE2 (SDAT) and PE3 (SCLK)
        
        // Set the SDAT pin based on the current bit of str
        if (str & (1 << (7 - j)))  // Check if the current bit is 1 or 0
        {
            GPIO_PORTE_DATA_R |= 0x04;  // Set SDAT (PE2) high if bit is 1
        }
        else
        {
            GPIO_PORTE_DATA_R &= ~0x04;  // Set SDAT (PE2) low if bit is 0
        }

        // Generate a clock pulse (PE3)
        GPIO_PORTE_DATA_R |= 0x08;  // Set SCLK (PE3) high
        GPIO_PORTE_DATA_R &= ~0x08; // Set SCLK (PE3) low
    }

    // Optionally, latch the data with a high signal on PE4 (depending on your hardware setup)
    GPIO_PORTE_DATA_R |= 0x10;  // Set PE4 (latch pin) high
    GPIO_PORTE_DATA_R &= ~0x10; // Set PE4 (latch pin) low
}

// Delay function to generate an approximate delay in milliseconds
void delayMs(int n)
{
    int i, j;
    for(i = 0; i < n; i++)
        for(j = 0; j < 3180; j++) {}  // Adjusted loop count for approximately 1 ms delay
}
