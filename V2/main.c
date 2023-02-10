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

void puts(char *s){
    /*while (*s != 0){ 
        putc(*s);
        s++;
    }
    */
    while (*s) uartputc(*s++);

}

void entry(){
    //Configuração inicial do dispositivo UART
    uartinit();

    //move cursor para cima
    puts(CURSOR_TOP_LEFT);
    //limpa a tela
    puts(CLEAR_SCREEN);
    
    
    //Inicialização das funções
    puts(TITULO);
    puts(ITALICO);
    puts("\n           ---- Screamer Operating System (SOS) ---- <disse o kernel>                                           ");

  
    //limpa edições no texto
    puts(NONE_TXT);

    puts(RED_TXT);
    puts(ITALICO);
    puts(PISCA);
    puts("\n\n\t\t\t HELP!! \n\t\t\t\t HELP!!!!\n\t\t\t\t\t HAAAAAAAA!!!\n\n");

    
    int c;
    //limpa edições no texto
    puts(NONE_TXT);


    puts(RED_TXT);
    // teste do printf()
    puts("Numero: ");
    printlngn(-123, 10);
    //imprimindo resultado de uma divisão
    puts("Numero dividido por 10\n");
    printlngn(-123/10, 10);
    puts("Numero 4 em base 2(Binario)\n");
    printlngn(4, 2);
    puts("Numero 255 em base Hex\n");
    printlngn(255, 16);
    puts(NONE_TXT);
    uartputc('\n');
    //testa_variadics();
    char nome = 'A';
    printf("Ola %s", nome);

    for(;;){
        c = uartgetc();

        if (c == -1)
            continue;
        /*
        //13 == enter na tabela ASCII
        if(c == 13)
            puts("\n");

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
                puts(BACKSPACE);
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
    puts("Perímetro de triangulo com lados: ");
    printlng(3,10);
    puts(" ");
    printlng(4,10);
    puts(" ");
    printlng(5,10);
    puts(" ");
    puts(": ");
    printlngn(p,10);
    puts("\n");
    puts("Perímetro de retangulo com lado 8: ");
    printlngn(perimetro(4, 8, 8, 8, 8),10);

}

*/
