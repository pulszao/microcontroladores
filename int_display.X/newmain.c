// PIC16F877A Configuration Bit Settings

// 'C' source line config statements

// CONFIG
#pragma config FOSC = HS        // Oscillator Selection bits (HS oscillator)

#pragma config WDTE = OFF        // Watchdog Timer Enable bit (WDT enabled)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config BOREN = OFF       // Brown-out Reset Enable bit (BOR enabled)
#pragma config LVP = OFF         // Low-Voltage (Single-Supply) In-Circuit Serial Programming Enable bit (RB3/PGM pin has PGM function; low-voltage programming enabled)
#pragma config CPD = OFF        // Data EEPROM Memory Code Protection bit (Data EEPROM code protection off)
#pragma config WRT = OFF        // Flash Program Memory Write Enable bits (Write protection off; all program memory may be written to by EECON control)
#pragma config CP = OFF         // Flash Program Memory Code Protection bit (Code protection off)

#include <stdint.h>
#include <xc.h>

#define _XTAL_FREQ 20000000      // Frequ�ncia do oscilador (20 MHz)
unsigned long cont = 0;

void __interrupt() intTempo(void);

void main(void) {
    
    TRISC = 0X00;
    
    // Configura��o do Timer 0
    OPTION_REGbits.T0CS = 0;   // Utiliza o oscilador do microcontrolador para o Timer 0
    OPTION_REGbits.PSA = 0;    // Associa o prescaler ao Timer 0
    OPTION_REGbits.PS = 0b000;

    // Configura��o das interrup��es
    INTCONbits.GIE = 1; // Habilita interrup��es globais
    INTCONbits.T0IE = 1; // Habilita interrup��o do Timer 0

    while (1) {
    }
    return;
}

void __interrupt() intTempo(void) {
    if (T0IF) {
        if(LED == 0){ // verifica se led esta ligado
            PORTBbits.RB0 = 1; // seleciona display
            PORTBbits.RB1 = 0;
            PORTBbits.RB2 = 0;
            PORTB = 0b00000000; // numero desejado
            LED = 1;
        } else if (LED == 1) {
            PORTBbits.RB0 = 0; // seleciona display
            PORTBbits.RB1 = 1;
            PORTBbits.RB2 = 0;
            PORTB = 0b00000000; // numero desejado
            LED = 2;
        } else {
            PORTBbits.RB0 = 0; // seleciona display
            PORTBbits.RB1 = 0;
            PORTBbits.RB2 = 1;
            PORTB = 0b00000000; // numero desejado
            LED = 0;
        }
    }
}