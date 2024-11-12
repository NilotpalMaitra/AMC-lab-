#include <stdint.h>
#include "tm4c123gh6pm.h"

void UART0Tx(char c);
void delayMs(int n);

int main(void)
{
    // Enable clock to UART0 and PORTB
    SYSCTL->RCGCUART |= 2;    // Provide clock to UART0
    SYSCTL->RCGCGPIO |= 2;    // Enable clock to PORTB

    // UART0 initialization
    UART0->CTL = 0;           // Disable UART0
    UART0->IBRD = 104;        // 16 MHz / 16 = 1 MHz, 1 MHz / 104 = 9600 baud
    UART0->FBRD = 11;         // Fraction part
    UART0->CC = 0;            // Use system clock
    UART0->LCRH = 0x60;       // 8-bit, no parity, 1 stop bit, no FIFO
    UART0->CTL = 0x301;       // Enable UART0, TXE, RXE

    // UART0 TX0 and RX0 use PB0 and PB1. Set them up.
    GPIOB->DEN = 0x03;        // Make PB0 and PB1 digital
    GPIOB->AFSEL = 0x03;      // Use PB0, PB1 alternate function
    GPIOB->PCTL = 0x11;       // Configure PB0 and PB1 for UART
    GPIOB->AMSEL = 0x00;      // Disable analog functionality on PB0 and PB1

    delayMs(1);               // Wait for output line to stabilize

    // Send characters via UART
    UART0Tx('E');
    UART0Tx('N');
    UART0Tx('T');
    UART0Tx('E');
    UART0Tx('R');
    UART0Tx(' ');
    UART0Tx('T');
    UART0Tx('E');
    UART0Tx('X');
    UART0Tx('T');
    UART0Tx(':');

    while(1);  // Infinite loop to end the program
}

// UART0 Transmit
// This function waits until the transmit buffer is available then
// writes the character in the transmit buffer.
void UART0Tx(char c)
{
    while((UART0->FR & 0x20) != 0);   // Wait until Tx buffer is not full
    UART0->DR = c;                     // Transmit the character
}

// Delay function to generate an approximate delay in milliseconds
void delayMs(int n)
{
    int i, j;
    for(i = 0; i < n; i++)
        for(j = 0; j < 3180; j++) {}  // Adjusted for ~1 ms delay
}
