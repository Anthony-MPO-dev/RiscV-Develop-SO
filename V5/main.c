#define uart_base 0x10000000
#include "defs_SOS.h"
#include "console.h"

/* substrituido pelo uart putc
static void putc(char c){
    char *reg;
    // (reg == 0x10000000)
    reg = (char *) uart_base;
    *reg = c;
}
*/

void printlng(long, int);
void printlngn(long, int);
void printf(char *s, ...);

/*
void puts(char *s){
    //while (*s != 0){ 
    //    putc(*s);
    //    s++;
    //}
    
    while (*s) uartputc(*s++);

}
*/

void entry(){
    //Configuração inicial do dispositivo UART
    uartinit();

    //move cursor para cima
    printf(CURSOR_TOP_LEFT);
    //limpa a tela
    printf(CLEAR_SCREEN);
    
    
    //Inicialização das funções
    printf(TITULO);
    printf(ITALICO);
    printf(BOLD);
    printf("\n           ---- Screamer Operating System (SOS) ---- <disse o kernel>                                           ");
    memory_init();
  
    //limpa edições no texto
    printf(NONE_TXT);

    printf(RED_TXT);
    printf(ITALICO);
    printf(PISCA);
    printf("\n\n\t\t\t HELP!! \n\t\t\t\t HELP!!!!\n\t\t\t\t\t HAAAAAAAA!!!\n\n");

    
    int c;
    //limpa edições no texto
    printf(NONE_TXT);


    printf(RED_TXT);
    /*
    // teste do printf()
    printf("Numero: ");
    
    printf("Decimal: %d\nHexadecimal %x\n", -123 / 4, 255);
    char *s = "Teste de ponteiro";
    printf("Endereço da string literal: %p\n", s);
    printf("string: %s\n", s);
    printf("funcao invalida: %f\n", s);

    */

    //printlngn(-123, 10);
    //imprimindo resultado de uma divisão
    //printf("Numero dividido por 10\n");
    //printlngn(-123/10, 10);
    //printf("Numero 4 em base 2(Binario)\n");
    //printlngn(4, 2);
    //printf("Numero 255 em base Hex\n");
    //printlngn(255, 16);
    printf(NONE_TXT);
    uartputc('\n');
    uartputc('\n');
    //testa_variadics();
    char *nome = "USUARIO";
    printf("Ola %s tudo %d%%?\n", nome, 100);
    uartputc('\n');
    uartputc('\n');

    for(;;){
        c = uartgetc();

        if (c == -1)
            continue;
        /*
        //13 == enter na tabela ASCII
        if(c == 13)
            printf("\n");

        if( c == '\r' ){
            uartputc('\r');
            uartputc('\n');
        }
        */
        	
        switch(c){
            case '\r':
                uartputc('\r');
                uartputc('\n');
                break;
            case 127://del
                //uartputc('\b');
                //uartputc(' ');
                //uartputc('\b');
                printf(BACKSPACE);
                break;
            default:
                uartputc(c);
        }
    }
}

/*
void testa_variadics(){
    int p;
    //Perimetro de triângulo
    p = perimetro(3, 3, 4, 5);
    printf("Perímetro de triangulo com lados: ");
    printlng(3,10);
    printf(" ");
    printlng(4,10);
    printf(" ");
    printlng(5,10);
    printf(" ");
    printf(": ");
    printlngn(p,10);
    printf("\n");
    printf("Perímetro de retangulo com lado 8: ");
    printlngn(perimetro(4, 8, 8, 8, 8),10);

}

*/
