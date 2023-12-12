#include <xc.h>
#include <stdint.h>
#include <string.h>

#pragma config FOSC = HS
#pragma config WDTE = OFF
#pragma config PWRTE = OFF
#pragma config BOREN = OFF
#pragma config LVP = ON
#pragma config CPD = OFF
#pragma config WRT = OFF
#pragma config CP = OFF

#define LED PORTDbits.RD0

#define RW_LCD PORTDbits.RD1
#define RS_LCD PORTDbits.RD2
#define E_LCD  PORTDbits.RD3
#define D4_LCD PORTDbits.RD4
#define D5_LCD PORTDbits.RD5
#define D6_LCD PORTDbits.RD6
#define D7_LCD PORTDbits.RD7

void posdp(int ValorP);
void escrevedp(char dado);
void escrevedp_ini(char dado);
void tempo_disp(void);
void ini_display(void);
void limpa_disp(void);
void display(int posicao, char *mens);
void display_escreve_int(int Num);
void le_teclado();
void enviarByte(unsigned char byte);
void definirCorRGB(unsigned char vermelho, unsigned char verde, unsigned char azul);

#define _XTAL_FREQ 20000000  

#define PINO_RGB PORTAbits.RA0

#define enviarBit(b) PINO_RGB = 1; PINO_RGB = 1; PINO_RGB = b; PINO_RGB = b; PINO_RGB = 0; PINO_RGB = 0;

void main(void)
{
    TRISA = 0; // Configurar RA0 como saída
    TRISD = 0; // saida do LCD
    TRISC = 0xF0; // saida teclado
   
    ini_display();
    limpa_disp();
   
    while (1) {
        le_teclado();
        
        // Aguarde um curto período para evitar leituras repetidas
        __delay_ms(10);
    }

    return;
}

void enviarByte(unsigned char byte)
{
    if (byte & 0b10000000) { enviarBit(1); }
    else { enviarBit(0); }

    if (byte & 0b01000000) { enviarBit(1); }
    else { enviarBit(0); }

    if (byte & 0b00100000) { enviarBit(1); }
    else { enviarBit(0); }

    if (byte & 0b00010000) { enviarBit(1); }
    else { enviarBit(0); }

    if (byte & 0b00001000) { enviarBit(1); }
    else { enviarBit(0); }

    if (byte & 0b00000100) { enviarBit(1); }
    else { enviarBit(0); }

    if (byte & 0b00000010) { enviarBit(1); }
    else { enviarBit(0); }

    if (byte & 0b00000001) { enviarBit(1); }
    else { enviarBit(0); }
}

void definirCorRGB(unsigned char vermelho, unsigned char verde, unsigned char azul)
{
    enviarByte(vermelho);
    enviarByte(verde);
    enviarByte(azul);
}

void le_teclado() {
    char caractere;
    // Configurações iniciais
    PORTCbits.RC0 = 0;
    PORTCbits.RC1 = 1;
    PORTCbits.RC2 = 1;
    PORTCbits.RC3 = 1;
   
    // COLUNA 4 ----------------------------------------------------------------
    if (RC4 == 0) {
        caractere = 'D';
        definirCorRGB(64, 64, 64);
            limpa_disp();
            display(0x80, "Branco");  
            display(0xC0, "Intensidade: 1");
    } else if (RC5 == 0) {
        caractere = 'C';
        definirCorRGB(0, 0, 64);
            limpa_disp();
            display(0x80, "Azul");  
            display(0xC0, "Intensidade: 1");
    } else if (RC6 == 0) {
        caractere = 'B';
        definirCorRGB(0, 64, 0);
            limpa_disp();
            display(0x80, "Verde");  
            display(0xC0, "Intensidade: 1");
    } else if (RC7 == 0) {
        caractere = 'A';
        definirCorRGB(64, 0, 0);
            limpa_disp();
            display(0x80, "Vermelho");  
            display(0xC0, "Intensidade: 1");
    
    // COLUNA 3 ----------------------------------------------------------------
    } else {
        PORTCbits.RC1 = 0;
        if (RC4 == 0) {
            caractere = '#';
            definirCorRGB(120, 120, 120);
            limpa_disp();
            display(0x80, "Branco");  
            display(0xC0, "Intensidade: 2");
        } else if (RC5 == 0) {
            caractere = '9';
            definirCorRGB(0, 0, 120);
            limpa_disp();
            display(0x80, "Azul");  
            display(0xC0, "Intensidade: 2");
        } else if (RC6 == 0) {
            caractere = '6';
            definirCorRGB(0, 120, 0);
            limpa_disp();
            display(0x80, "Verde");  
            display(0xC0, "Intensidade: 2");
        } else if (RC7 == 0) {
            caractere = '3';
            definirCorRGB(120, 0, 0);
            limpa_disp();
            display(0x80, "Vermelho");  
            display(0xC0, "Intensidade: 2");
        } else {
            
    // COLUNA 2 ----------------------------------------------------------------
            PORTCbits.RC2 = 0;
            if (RC4 == 0) {
                caractere = '0';
                definirCorRGB(190, 190, 190);
                limpa_disp();
                display(0x80, "Branco");  
                display(0xC0, "Intensidade: 3");
            } else if (RC5 == 0) {
                caractere = '8';
                definirCorRGB(0, 0, 190);
                limpa_disp();
                display(0x80, "Azul");  
                display(0xC0, "Intensidade: 3");
            } else if (RC6 == 0) {
                caractere = '5';
                definirCorRGB(0, 190, 0);
                limpa_disp();
                display(0x80, "Verde");  
                display(0xC0, "Intensidade: 3");
            } else if (RC7 == 0) {
                caractere = '2';
                definirCorRGB(190, 0, 0);
                limpa_disp();
                display(0x80, "Vermelho");  
                display(0xC0, "Intensidade: 3");
            } else {
                
    // COLUNA 1 ----------------------------------------------------------------
                PORTCbits.RC3 = 0;
                if (RC4 == 0) {
                    caractere = '*';
                    definirCorRGB(255, 255, 255);
                    limpa_disp();
                    display(0x80, "Branco");  
                    display(0xC0, "Intensidade: 4");
                } else if (RC5 == 0) {
                    caractere = '7';
                    definirCorRGB(0, 0, 255);
                    limpa_disp();
                    display(0x80, "Azul");  
                    display(0xC0, "Intensidade: 4");
                } else if (RC6 == 0) {
                    caractere = '4';
                    definirCorRGB(0, 255, 0);
                    limpa_disp();
                    display(0x80, "Verde");  
                    display(0xC0, "Intensidade: 4");
                } else if (RC7 == 0) {
                    caractere = '1';
                    definirCorRGB(255, 0, 0);
                    limpa_disp();
                    display(0x80, "Vermelho");
                    display(0xC0, "Intensidade: 4");
                    PORTBbits.RB0 = 1;    
                } else {
                    caractere = ' '; // espaço
                }
                // Restaura as configurações originais
                PORTCbits.RC3 = 1;
            }
            // Restaura as configurações originais
            PORTCbits.RC2 = 1;
        }
        // Restaura as configurações originais
        PORTCbits.RC1 = 1;
    }
    PINO_RGB = 0;
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
