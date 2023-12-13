# Projeto Final

Realizando a implementação de um hardware que utilizasse um teclado matricial 4x4, um display LCD 2x16 e uma placa RGB
modelo WS2811.
Além da PIC16F874A, utilziada para controlar os componentes.

## Funcionamento

Foi estabelecido que as linhas representam diferentes cores: vermelho na primeira linha, verde na segunda, azul na
terceira e branco na quarta. As colunas, por sua vez, determinam a intensidade luminosa. Dessa forma, a primeira coluna
representa a intensidade 4 (mais forte), a segunda coluna representa a intensidade 3 (forte), a terceira coluna
representa a intensidade 2 (média) e a última coluna representa a intensidade 1 (mais fraca). Simultaneamente ao
acionamento do RGB, ocorre a escrita no painel LCD, da cor selecionada e a intensidade correspondente, de acordo com a
tecla pressionada.

## Montagem

- Foram utilizadas duas fontes de alimentação, uma de 5 volts (alimentação da PIC) e outra de 9 volts (alimentação do
  led
  RGB) com suas saídas negativas interligadas;
- O display LCD foi conectado às portas RD0 - RD7;
- O teclado matricial às portas RC0 - RC7 (utilizando resistores de pull-up (4k7Ω) nos quatro pinos referentes às
  colunas
  do teclado);
- A placa RGB foi conectanda ao pino de comunicação na porta RA0.

## Firmware

- `enviarBit(b)` - Macro para enviar os valores dos bits para a pic;
- `void enviarByte(unsigned char byte)` - Rotina implementada para realizar a comunicação da placa com a pic;
- `void definirCorRGB(unsigned char vermelho, unsigned char verde, unsigned char azul)` - encarregada de transmitir os
  bytes correspondentes às cores, parâmetros são valores de 0 a 255;
- `void le_teclado()` - rotina que acende o led e escreve no display. Realiza iterações contínuas nas linhas do teclado.
  Quando uma linha está ativa, a rotina verifica as colunas para identificar a tecla pressionada pelo usuário.
