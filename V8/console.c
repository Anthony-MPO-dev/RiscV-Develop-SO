#include "types.h"
#include "defs_SOS.h"
#include "syscalls.h"
#include "console.h"


void console_handler(){
    int c;
    c = uartgetc();

    if (c == -1)
        return;
        
    switch(c){
        case '\r':
            uartputc('\r');
            uartputc('\n');
            break;
        case 127://del
            printf(BACKSPACE);
            break;
        case 'S':
            msg_syscall(8);
            break;
        case 'H':
            set_hostname("Anthony", 7);
            break;
        case 'B':
            halt();
            break;
        default:
            uartputc(c);
    }
}