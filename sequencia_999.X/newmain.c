/*
 * File:   newmain.c
 * Author: pulsz
 *
 * Created on September 13, 2023, 8:34 PM
 */

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

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.

#include <xc.h>

// Programa que conta de 0 a 999 em um display de 7 segmentos

unsigned char num_2_lcd(unsigned char valor);

void main(void) {
    unsigned int contador = 0;
    unsigned int contador_tempo = 0;
    unsigned long tempo = 0;
    TRISD = 0x00; // Display : output
    TRISC = 0x00; // Selecao do Display : output
    TRISA = 0x01; // Bot�es : input
    
    contador = 123;
    
    do
    {
        if(PORTAbits.RA0 == 0) {
            contador++;
            contador_tempo = 0;
        }
        if (contador_tempo > 20) {
            contador++;
            contador_tempo = 0;
        }
        if (contador_tempo > 999) {
            contador_tempo = 0;
        }
        
        PORTD = 0x01; // Display da centena
        PORTC = num_2_lcd(contador / 100); // Numero 3
        for (tempo=0;tempo<=0xFF;tempo++) continue;
        
        PORTD = 0x02; // Display da dezena
        PORTC = num_2_lcd((contador % 100) / 10); // Numero 2
        for (tempo=0;tempo<=0xFF;tempo++) continue;

        PORTD = 0x04; // Display da unidade
        PORTC = num_2_lcd(contador % 10); // Numero 1
        for (tempo=0;tempo<=0xFF;tempo++) continue;
        contador_tempo++;
        
        if(contador_tempo > 100) {
            contador++;
            contador_tempo = 0;
        }
    }while(1);
    return;
}

unsigned char num_2_lcd(unsigned char valor) {
    unsigned char valor_retorno;
    
    switch(valor) {
        case 0:
            return 0b00111111;
        case 1:
            return 0b00000110;
        case 2:
            return 0b01011011;
        case 3:
            return 0b01001111;
        case 4:
            return 0b01100110;
        case 5:
            return 0b01101101;
        case 6:
            return 0b01111101;
        case 7:
            return 0b00000111;
        case 8:
            return 0b01111111;
        case 9:
            return 0b01101111;
    }
}
