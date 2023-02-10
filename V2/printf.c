#include "types.h"
#include "defs_SOS.h"
#include <stdarg.h>

//static char digits[16] = {49,50,51 ... 70};
static char *digits = "0123456789ABCDEF";
//static - quando o programa começar ja estara criada e armazenada e apenas destruida no final da execução do programa

void 
printlng(long val, int base){
    long l;
    int i = 0; // 1ª posição livre do buffer - indice do buffer
    char s[65];// buffer para a respresentação ASCII do número

    

    if(val < 0){
        // Trabalhamos sempre com números positivos
        l = -val;
    }
    else
        l = val;

    if (l == 0)
       s[i++] = '0'; //  s[i++] = digits[l];
    while(l){ // enquanto l != 0
        /*
        1. Obtém o último digito do número
        2. Obtém o código ASCII do digito
        3. Armazeao código ASCII no buffer (s)
        4. Incrementa próx. posição livre do buffer
        */
        s[i++] = digits[l % base]; // base = 10
        l = l / base;
    }

    if(base == 2){
        s[i++] = 'b';
        s[i++] = '0';
    }

    if(base == 16){
        s[i++] = 'x';
        s[i++] = '0';
    }

    //adiciona sinal ao número negativo
    if(val < 0) s[i++] = '-';

    //Imprime do caracteres do buffer
    while(i > 0) uartputc(s[--i]);
}

printlngn(long val, int base){
    printlng(val, base);
    uartputc('\n');
}

/*
%d - int
%x -  hex
%l - long
%s - char
%p - pointer
*/



void
printf(char *s, ...){
    va_list ap; // ponteiro para a lista de argumentos de printf
    //char *str; // argumentos string
    va_start(ap, s);
    //percorre todos os elementros da string s
    while(*s != 0){
        
        if(*s == '%' ){
            *++s;
            switch (*s)
            {
            case 'd':
                printlng(va_arg(ap, int), 10);
                break;
            case 'x':
                printlng(va_arg(ap, int), 16);
                break;
            case 'l':
                printlng(va_arg(ap, int), 10);
                break;
            case 's':   
                uartputc((va_arg(ap, int)));
                break;
            
            default:
                break;
            }
            *++s;
        }
        uartputc(*s);
        *s++;
    }
         
}

