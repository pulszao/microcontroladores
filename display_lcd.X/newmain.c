/*
 * File:   newmain.c
 * Author: lcpulsz
 *
 * Created on 1 de Novembro de 2023, 19:27
 */

// CONFIG
#pragma config FOSC = HS        // Oscillator Selection bits (HS oscillator)
#pragma config WDTE = OFF        // Watchdog Timer Enable bit (WDT enabled)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config BOREN = OFF       // Brown-out Reset Enable bit (BOR enabled)
#pragma config LVP = ON         // Low-Voltage (Single-Supply) In-Circuit Serial Programming Enable bit (RB3/PGM pin has PGM function; low-voltage programming enabled)
#pragma config CPD = OFF        // Data EEPROM Memory Code Protection bit (Data EEPROM code protection off)
#pragma config WRT = OFF        // Flash Program Memory Write Enable bits (Write protection off; all program memory may be written to by EECON control)
#pragma config CP = OFF         // Flash Program Memory Code Protection bit (Code protection off)

#include <xc.h>

#define LED PORTCbits.RC4

#define RW_LCD PORTDbits.RD1
#define RS_LCD PORTDbits.RD2
#define E_LCD  PORTDbits.RD3

#define D4_LCD PORTDbits.RD4
#define D5_LCD PORTDbits.RD5
#define D6_LCD PORTDbits.RD6
#define D7_LCD PORTDbits.RD7

// OK: Escreve um texto pré determinado no display LCD 16x2 enquanto pisca LED

void ini_display(void);
void tempo_disp(void);
void escrevedp_ini(char dado);
void escrevedp(char dado);
void posdp(int ValorP);
void limpa_disp(void);
void display(int posicao, char *mens);

void main(void) 
{
    int cont = 0;
    //0=SAIDA 1=ENTRADA
    TRISD = 0x00;    
    TRISC = 0x00;

    
   	ini_display();
	limpa_disp();

    do {
        cont++;
        if(cont >= 4000){
            cont = 0;
            if(LED == 0){
                LED = 1;
            }
            else {
                LED = 0;
            }
        }
    } while(1);
    return;
}

void ini_display(void)
{
	RW_LCD = 0;
	RS_LCD = 0;

    E_LCD = 0;
    D4_LCD = 0;
    D5_LCD = 0;
    D6_LCD = 0;
    D7_LCD = 0;

	tempo_disp();
	tempo_disp();
	tempo_disp();
	tempo_disp();

    escrevedp_ini(0x3);
    escrevedp_ini(0x3);
	escrevedp_ini(0x3);
	escrevedp_ini(0x2);
	escrevedp_ini(0x2);
	escrevedp_ini(0x8);
	escrevedp_ini(0x0);
	escrevedp_ini(0xC);//F//8
	escrevedp_ini(0x0);
	escrevedp_ini(0x1);
	escrevedp_ini(0x0);
	escrevedp_ini(0x6);

	RS_LCD = 1;
}

void tempo_disp(void)
{
	unsigned int tempo;
	for(tempo = 0 ; tempo<0xFFF ;tempo++)
		continue;
}

void escrevedp_ini(char dado)
{
    D7_LCD = (dado&0x8)>>3;
    D6_LCD = (dado&0x4)>>2;
    D5_LCD = (dado&0x2)>>1;
    D4_LCD = (dado&0x1);

	tempo_disp();
	tempo_disp();
	tempo_disp();
	tempo_disp();
	tempo_disp();

    E_LCD=1;

	tempo_disp();
	tempo_disp();
	tempo_disp();
	tempo_disp();
	tempo_disp();

    E_LCD =0;

	tempo_disp();
	tempo_disp();
	tempo_disp();
	tempo_disp();
	tempo_disp();

}

void escrevedp(char dado)
{
    D7_LCD = (dado&0x80)>>7;
    D6_LCD = (dado&0x40)>>6;
    D5_LCD = (dado&0x20)>>5;
    D4_LCD = (dado&0x10)>>4;
    E_LCD =1;
    E_LCD =0;

	tempo_disp();

    D7_LCD = (dado&0x8)>>3;
    D6_LCD = (dado&0x4)>>2;
    D5_LCD = (dado&0x2)>>1;
    D4_LCD = (dado&0x1);
    E_LCD = 1;
    E_LCD = 0;
	tempo_disp();
}

void posdp(int ValorP)
{
	RS_LCD = 0;
	escrevedp(ValorP);
	RS_LCD = 1;
}

void limpa_disp(void)
{
	RS_LCD = 0;
	escrevedp_ini(0x0);
	escrevedp_ini(0x1);
	RS_LCD = 1;
}

void display(int posicao, char *mens)
{

	unsigned char cont_posicao;
	unsigned char tam_mensagem;
	char *bkp_mensagem;

	tam_mensagem = 0;

	bkp_mensagem = mens;
	
	//calcula tamanho da mensagem
	while((*bkp_mensagem)!=0)
	{
		//escreve posi??o do caracter no display
	    bkp_mensagem++;
		tam_mensagem++;
	}
	
	//converte posi??o para endere?o reconhecido pelo display      
	if(posicao>=1 && posicao<=16) 
		posicao= (posicao-1) + 0x80;  
	else if(posicao>=17 && posicao<=32) 
		posicao= (posicao-17) + 0xC0;  
	else 
		return;               

	cont_posicao=0;
	//escreve o buffer no display
	while((*mens)!=0 && (cont_posicao<17))
	{
		//escreve posi??o do caracter no display
		posdp(posicao);
		posicao++;
		cont_posicao++;	
		//escreve caracter no display
		escrevedp(*mens);
	    mens++;
	}
}
