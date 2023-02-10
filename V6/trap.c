#include "types.h"
#include "proc.h"
#include "defs_SOS.h"
/*
Tratamento das exceções
*/

void mtrap(uint64 tval, uint64 cause, TrapFrame *tf){
    if((long) cause > 0){
        //Exceção sincrona
        switch (cause){
            case 2: //Instrução ilegal
                printf("<Trap> Instrução ilegal [CPU#:%d] epc: %p tval: %p\n",tf->hartid, (uint64 *)tf->epc, (uint64 *)tval);
                tf->epc = tf-> epc + 4; // Instrução seguinte à que causou a exceção 
                break;
            
            case 9: // Chamada de sistema no modo-S
                printf("<Trap> Chamada de sistema!\n");
                break;
            default:
                //
                break;
        }
    }
    else{
        //Interupção
    }
}