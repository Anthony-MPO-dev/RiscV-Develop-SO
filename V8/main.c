#define uart_base 0x10000000
#include "types.h"
#include "defs_SOS.h"
#include "console.h"
#include "riscv.h"
#include "memlayout.h"
#include "syscalls.h"

// declarações
extern void mvector(void);

void printlng(long, int);
void printlngn(long, int);
void printf(char *s, ...);


void main(){    
    uartinit();    
    plic_init();
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

   

  
    //limpa edições no texto
    printf(NONE_TXT);

    r_mstatus();

    //tempo de execução
    //tempo_syscall();
    //tempo_syscall();
    //tempo_syscall();
    // Se ocorre interrupções ou exceções o hardware interrompe o laço e salta para
    //a rotina mvector (trap_handler.s), voltando para ca em seguida

    printf(RED_TXT);

    printf(NONE_TXT);
    uartputc('\n');
    uartputc('\n');
    char *nome = "USUARIO";
    printf("Ola %s tudo %d%%?\n", nome, 100);
    uartputc('\n');
    uartputc('\n');

    printf(S_TXT);
    printf(BOLD);

     for(;;);

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

    //Habilitar interrupções
    //mstatus.MPIE := 1
    x = x | (1 << 7);
    w_mstatus(x);

    // Habilita interrupção do temporizador e 
    // interrupções externas
    x = r_mie();
    x = x | (1 <<7); //MTIE (temporizador)
    x = x | (1 <<11); //MEIE (interrupções externas)
    w_mie(x);

    //O sistema gera uma interrupção a cada segundo
    uint64 *mtimecmp =(uint64*) CLINT_MTIMECMP(0); //CPU #
    uint64 *mtime = (uint64 *) CLINT_MTIME;
    *mtimecmp = *mtime + 10000000;
    //se mtime > mtimecmp o sistema gera interrupção do temporizador

    //Mudar para modo-S
    w_mepc((uint64) main);
    // Altera modo p/ Modo-S e salta para main
    asm volatile("mret");
}

