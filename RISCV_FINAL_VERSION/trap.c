#include "types.h"
#include "proc.h"
#include "defs_SOS.h"
#include "console.h"
#include "memlayout.h"

int segundos, h, m, s, resto;
/*
Tratamento das exceções
*/

void mtrap(uint64 tval, uint64 cause, TrapFrame *tf){
    uint64 *mtimecmp = (uint64 *) CLINT_MTIMECMP(0);

    if((long) cause > 0){
        //Exceção sincrona
        switch (cause){
            case 2: //Instrução ilegal
                printf("<Trap> Instrução ilegal [CPU#:%d] epc: %p tval: %p\n",tf->hartid, (uint64 *)tf->epc, (uint64 *)tval);
                tf->epc = tf-> epc + 4; // Instrução seguinte à que causou a exceção 
                break;
            
            case 9: // Chamada de sistema no modo-S
                if(tf-> a7 == 1){ // identificador da syscall
                    //msg_syscall
                    //Primeiro argumento da syscall em tf->a0
                    printf("\n<Trap> Chamada de sistema msg_syscall [id#: %d, arg#1: %d]", tf->a7, tf->a0);
                }
                if(tf-> a7 == 2){ // identificador da syscall
                    //set_hostname
                    printf("\n<Trap> Chamada de sistema set_hostname [nome do host: %s, tamanho: %d]", tf->a0, tf->a1);
                }
                if(tf-> a7 == 3){ // identificador da syscall
                    //PANIC
                    printf(RED_TXT);
                    printf(PISCA);
                    panic("Tecla da morte precionada");  
                }
                 if(tf-> a7 == 4){ // identificador da syscall
                        //Tempo do sistema

                        //Pega os segundos de funcionamento do sistema
                        segundos = *mtimecmp/10000000;  

                        //Calcula horas
                        h = segundos / 3600;
                        resto = segundos % 3600;
                        //Calcula minutos
                        m = resto / 60;
                        //Calcula Segundos
                        s = resto % 60;

                        printf(NONE_TXT);
                        printf("\n \u23F0 %d:%d:%d\n", h, m, s); 
                    
                }
                
                tf->epc = tf->epc + 4;//o hw retorna para a instrução seguinte à ecall
                break;
            default:
                //
                break;
        }
    }
    else{
        //Interrupção
        cause = cause & 0xfff;//Seleciona os ultimos 12bits de cause
        switch(cause){
            case 7:
                //interrupção do relogio do temporizador
                //printf("\n \u23F0 Interrupção do temporizador <modo-S>");
                //Atualizar proxima interrupçao em 1 segundo
                *mtimecmp = *(uint64 *) CLINT_MTIME + 10000000;
                break;
        }
    }
}