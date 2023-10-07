
// PIC16F874A Configuration Bit Settings

// 'C' source line config statements

// CONFIG
#pragma config FOSC = HS        // Oscillator Selection bits (HS oscillator)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config BOREN = OFF      // Brown-out Reset Enable bit (BOR disabled)
#pragma config LVP = OFF        // Low-Voltage (Single-Supply) In-Circuit Serial Programming Enable bit (RB3 is digital I/O, HV on MCLR must be used for programming)
#pragma config CPD = OFF        // Data EEPROM Memory Code Protection bit (Data EEPROM code protection off)
#pragma config WRT = OFF        // Flash Program Memory Write Enable bits (Write protection off; all program memory may be written to by EECON control)
#pragma config CP = OFF         // Flash Program Memory Code Protection bit (Code protection off)

// Programa para fazer um display de 7 segmentos contar de 0 a 9

#include <xc.h>

#define _XTAL_FREQ 20000000


void main(void) {
    
    TRISC = 0;
    TRISD = 0;
    
    while (1) {
        PORTD = 0x01;
        
        PORTC = 0b00111111; // 0
        __delay_ms(1000);
        PORTD = 0x02; // display 2 (0b0010)
        PORTC = 0b00000110; // 1
        __delay_ms(1000);
        PORTD = 0x04; // display 3 (0b0100)
        PORTC = 0b01011011; // 2
        __delay_ms(1000);
        PORTC = 0b01001111; // 3
        __delay_ms(1000);
        PORTC = 0b01100110; // 4
        __delay_ms(1000);
        PORTC = 0b01101101; // 5
        __delay_ms(1000);
        PORTC = 0b01111101; // 6
        __delay_ms(1000);
        PORTC = 0b00000111; // 7
        __delay_ms(1000);
        PORTC = 0b01111111; // 8
        __delay_ms(1000);
        PORTC = 0b01101111; // 9
        __delay_ms(1000);
        
    };
    
    return;
}
