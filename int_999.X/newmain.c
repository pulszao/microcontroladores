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

// OK: escreve de 0 a 999 em 3 displays de 7 segmentos diferentes utilizando interrupção

#define _XTAL_FREQ 20000000      // Frequência do oscilador (20 MHz)
unsigned long cont = 0;
int number = 0;
unsigned long tempo = 0;
unsigned long LED = 0;
int unidade = 0;
int centena = 0;
int dezena = 0;

void __interrupt() intTempo(void);
unsigned char converte2bcd(int digit);

void main(void) {    
    TRISC = 0X00;
    TRISD = 0x00;

    // Configuração do Timer 0
    OPTION_REGbits.T0CS = 0;   // Utiliza o oscilador do microcontrolador para o Timer 0
    OPTION_REGbits.PSA = 0;    // Associa o prescaler ao Timer 0
    OPTION_REGbits.PS = 0b000;

    // Configuração das interrupções
    INTCONbits.GIE = 1; // Habilita interrupções globais
    INTCONbits.T0IE = 1; // Habilita interrupção do Timer 0

    centena = 0b00111111;
    dezena =  0b00111000;
    unidade = 0b01110111;    
    for(tempo=0;tempo<=0xFFFFF;tempo++);
 
    while (1) {
        tempo++;
        if (tempo>0xFF70) {
            number++;
            tempo=0;
            centena = converte2bcd(number / 100);
            dezena = converte2bcd((number % 100) / 10);
            unidade = converte2bcd((number % 10));
            
        }
        
        if(number==999) {
            number=0;
        }
    }
    return;
}

void __interrupt() intTempo(void) {
    if (T0IF) {
//        centena = number / 100;
//        dezena = (number % 100) / 10;
//        unidade = (number % 10);
        
        if(LED == 0){ // verifica se led esta ligado
            PORTCbits.RC0 = 0; // seleciona display
            PORTCbits.RC1 = 0;
            PORTCbits.RC2 = 1;
            PORTD = centena;
            LED = 1;
        } else if (LED == 1) {
            PORTCbits.RC0 = 0; // seleciona display
            PORTCbits.RC1 = 1;
            PORTCbits.RC2 = 0;
            PORTD = dezena;  
            LED = 2;
        } else {
            PORTCbits.RC0 = 1; // seleciona display
            PORTCbits.RC1 = 0;
            PORTCbits.RC2 = 0;
            PORTD = unidade; 
            LED = 0;
        } 
    T0IF = 0;
    }
}

unsigned char converte2bcd(int valor) {
    unsigned char retorno;
    switch(valor) {
        case 0:
            retorno =  0b00111111;
            break;
        case 1:
            retorno =  0b00000110;
            break;
        case 2:
            retorno =  0b01011011;
            break;
        case 3:
            retorno =  0b01001111;
            break;
        case 4:
            retorno =  0b01100110;
            break;
        case 5:
            retorno =  0b01101101;
            break;
        case 6:
            retorno =  0b01111101;
            break;
        case 7:
             retorno =  0b00000111;
            break;
        case 8:
            retorno =  0b01111111;
            break;
        case 9:
            retorno =  0b01101111;
            break;
    }
    return(retorno);
}