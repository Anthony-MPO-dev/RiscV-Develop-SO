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

void puts(char *s){
    /*while (*s != 0){ 
        putc(*s);
        s++;
    }
    */
    while (*s) uartputc(*s++);

}

void entry(){
    //move cursor para cima
    puts(CURSOR_TOP_LEFT);
    //limpa a tela
    puts(CLEAR_SCREEN);
    
    
    //Inicialização das funções
    puts("\n -- Screaming Operating System (SOS) -- <disse o kernel> \n HELP!! \n HELP!!!!\n HAAAAAAAA!!!\n\n");
    int c;

    //Configuração inicial do dispositivo UART
    uartinit();
    
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
