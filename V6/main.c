#define uart_base 0x10000000
#include "defs_SOS.h"
#include "console.h"
#include "riscv.h"

// declarações
extern void mvector(void);


void printlng(long, int);
void printlngn(long, int);
void printf(char *s, ...);


void main(){    
    uartinit();    

    //Inicialização das funções
    printf(TITULO);
    printf(ITALICO);
    printf(BOLD);
    printf("\n           ---- Screamer Operating System (SOS) ---- <disse o kernel>                                           ");
  
    //limpa edições no texto
    printf(NONE_TXT);

    printf(RED_TXT);
    printf(ITALICO);
    printf(PISCA);
    printf("\n\n\t\t\t HELP!! \n\t\t\t\t HELP!!!!\n\t\t\t\t\t HAAAAAAAA!!!\n\n");

   

    int c;
    //limpa edições no texto
    printf(NONE_TXT);

    r_mstatus();

    printf(RED_TXT);

    printf(NONE_TXT);
    uartputc('\n');
    uartputc('\n');
    char *nome = "USUARIO";
    printf("Ola %s tudo %d%%?\n", nome, 100);
    uartputc('\n');
    uartputc('\n');

    for(;;){
        c = uartgetc();

        if (c == -1)
            continue;
       
        	
        switch(c){
            case '\r':
                uartputc('\r');
                uartputc('\n');
                break;
            case 127://del
                printf(BACKSPACE);
                break;
            default:
                uartputc(c);
        }
    }
}

void entry(){
    memory_init();
    //Rotina para salvar o contexto
    uint64 x = (uint64) mvector; 
    w_mtvec(x);

    /*

    Alterar registrador mstatus para permitir mudança de modo
    Objetivo: mudar para modo-S (supervisor)
    */
    x = r_mstatus();
    //Coloca os bits 12 e 11 para o valor 01
    x = x & ~(3L << 11); // limpa os bits 12 e 11
    x = x | (1L << 11);// seta os bits 12 e 11 para 01 respectivamente
    w_mstatus(x);

    //Mudar para modo-S
    w_mepc((uint64) main);
    // Altera modo p/ Modo-S e salta para main
    asm volatile("mret");
}

