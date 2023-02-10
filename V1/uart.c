#include "types.h"
#include "memlayout.h"

// Registradores do UART:
#define RHR 0 // Registrador para leitura
#define THR 0 // Registrador para transmissão 
#define IER 1 // Registrador para habilitar/desabilitar interupção
#define FCR 2 // Registrador para buffer FIFO
#define ISR 2 // Registrador de Status da interrupção 
#define LCR 3 // 
#define LSR 5 // Registrador Status da linha

//prototipos
void write_reg(uint8, char);
char read_reg(uint8);
void uartinit();

char 
read_reg(uint8 reg){
    //Leitura de um registrador UART
    char c;
    volatile uint8 *base = (uint8 *) UART;
    c = *(base + reg);
    return c;
}

void
write_reg(uint8 reg, char c){
    volatile uint8 *base = (uint8*) UART;
    *(base + reg) = c;
}

void
uartinit(){
    // tamanho dos dados: 8 bits
    write_reg(LCR, 0x3);
    //habilita buffer
    write_reg(FCR, 0x1);
    //habilita interrupção de recebimento de dados
    write_reg(IER, 0x1);
}

//imprime caractere no terminal
void
uartputc(int c){
    while((read_reg(LSR) & (1 << 5))== 0)
    ;
    write_reg(THR, c);
}

//Fazer um uartgetc
int
uartgetc(){
    int c;

    
    //Ha dado disponivel para letura?
    if((read_reg(LSR) & (0x1)) != 1)
        return -1; 
    
    c = read_reg(RHR);//Chama o registrador para leitura
    return c;
    
}