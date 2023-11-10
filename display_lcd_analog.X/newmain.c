/*
 * File:   newmain.c
 * Author: lcpulsz
 *
 * Created on 8 de Novembro de 2023, 21:14
 */

#include <xc.h>
#include <stdint.h>

#pragma config FOSC = HS        // Oscillator Selection bits (HS oscillator)
#pragma config WDTE = OFF        // Watchdog Timer Enable bit (WDT enabled)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config BOREN = OFF       // Brown-out Reset Enable bit (BOR enabled)
#pragma config LVP = ON         // Low-Voltage (Single-Supply) In-Circuit Serial Programming Enable bit (RB3/PGM pin has PGM function; low-voltage programming enabled)
#pragma config CPD = OFF        // Data EEPROM Memory Code Protection bit (Data EEPROM code protection off)
#pragma config WRT = OFF        // Flash Program Memory Write Enable bits (Write protection off; all program memory may be written to by EECON control)
#pragma config CP = OFF         // Flash Program Memory Code Protection bit (Code protection off)

//Declara??o de Func?es
void posdp(int ValorP);
void escrevedp(char dado);
void escrevedp_ini(char dado);
void tempo_disp(void);
void ini_display(void);
void limpa_disp(void);
void display(int posicao, char *mens);
void display_escreve_int(int Num);
void mostra_numero(unsigned char posicao, unsigned int valor);
void conversao_AD();

#define LED PORTDbits.RD0

#define RW_LCD PORTDbits.RD1
#define RS_LCD PORTDbits.RD2
#define E_LCD  PORTDbits.RD3

#define D4_LCD PORTDbits.RD4
#define D5_LCD PORTDbits.RD5
#define D6_LCD PORTDbits.RD6
#define D7_LCD PORTDbits.RD7

unsigned char Num = 1;
//uint16_t valorDigital;
unsigned int valorad;
float tensao;
unsigned int contador = 0;

void main(void)
{

    ADCON1bits.ADFM = 0b1;
    ADCON0bits.CHS  = 0b000;
    ADCON0bits.ADCS = 0b01;
    ADCON1bits.PCFG = 0b1110;
    ADCON0bits.ADON = 0b1;
   
    int tempo;    
    //0=SAIDA 1=ENTRADA
    TRISD = 0;
    TRISB = 0x00;

    ini_display();
    limpa_disp();
   
   
    do
    {
        conversao_AD();
        Num++;
        mostra_numero(1,Num);
        mostra_numero(18, valorad);
        
        tensao = ((5*valorad)/950)*100;
        mostra_numero(22, tensao);
       
    }while(1);
    return;
}
void mostra_numero(unsigned char posicao, unsigned int valor)
{
    if (posicao > 17)
        posicao = posicao + 0xC0 - 17;
    else
        posicao = posicao + 0x80 - 1;
    posdp(posicao);
    
    escrevedp(valor/100 + '0');
    escrevedp((valor%100)/ 10 + '0');
    escrevedp(valor%10 + '0');
}

void conversao_AD()
{
    ADCON0bits.CHS = 0b0000; // seta canal analogico
    ADCON0bits.GO  = 0b1; // inicia conversao analog/digital
   
    while(ADCON0bits.GO_DONE == 1); 
   
    valorad = ADRESH;
    valorad = (valorad << 8); // shifta 8 bits para a esquerda
    valorad = valorad | ADRESL; // adiciona os bits menos significativos a variavel
   
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
for(tempo = 0 ; tempo<0xFF ;tempo++)
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
           

cont_posicao=0;
//escreve o buffer no display
while((*mens)!=0 && (cont_posicao<17))
{
//escreve posi??o do caracter no display
posdp(posicao);
posicao++;
cont_posicao++;
//escreve caracter no display
escrevedp(*mens);//char[0]//v
   mens++;
}
}

void display_escreve_int(int numdp)
{
    numdp = numdp+48;
   
D7_LCD = (numdp&0x80)>>7;
    D6_LCD = (numdp&0x40)>>6;
    D5_LCD = (numdp&0x20)>>5;
    D4_LCD = (numdp&0x10)>>4;
    E_LCD =1;
    E_LCD =0;

tempo_disp();

    D7_LCD = (numdp&0x8)>>3;
    D6_LCD = (numdp&0x4)>>2;
    D5_LCD = (numdp&0x2)>>1;
    D4_LCD = (numdp&0x1);
    E_LCD = 1;
    E_LCD = 0;
tempo_disp();
}

void display_int(int posicao, char *mens)
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
           

cont_posicao=0;
//escreve o buffer no display
while((*mens)!=0 && (cont_posicao<17))
{
//escreve posi??o do caracter no display
posdp(posicao);
posicao++;
cont_posicao++;
//escreve caracter no display
escrevedp(*mens);//char[0]//v
   mens++;
}
}