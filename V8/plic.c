#include "types.h"
#include "memlayout.h"

//Habilita interrupção de número irq. Ex.: UART tem irq 10.
//Cada interrupção é um bit da word de 32 bits.

void 
plic_enable(int irq){
    uint32 *enable = (uint32 *) PLIC_ENABLE; //(uint32 *) 0xc0002000 
    *enable = *enable | (1<<irq);

}

void 
plic_priority(uint32 irq, uint8 prio){
    // *(uint32 *)(PLIC_PRIORITY + irq * 4) = prio & 7;
    uint32  *priority = (uint32 *)(PLIC_PRIORITY + irq * 4); //0xc0000000
    *priority = prio & 7;//Maior prioridade válida é 7    
}

void
plic_threshold(uint8 thresh){
    uint32 *t = (uint32 *) PLIC_THRESHOLD;
    *t = thresh & 7;
}

//Quem interrompe?
//numero da interrupção que aconteceu (esta com maior prioridade no momento)
uint32
plic_claim(){
    return * (uint32 *) PLIC_CLAIM;
}

//informar que o kernel atendeu a interrupção irq 
void plic_complete(uint32 irq){
    *(uint32 *) PLIC_CLAIM = irq;
}

void
plic_init(){
    //todas as interrupções menor ou igual ao threshold serão mascaradas
    //(desconsideradas). No caso, vamos atender todas as que ocorrem (threshold == 0).
    //-Habilitamos apenas a interrupção UART e configura sua prioridade para 1
    plic_threshold(0);
    plic_enable(UART_IRQ);
    plic_priority(UART_IRQ, 1);
}