#include "types.h"

struct trap_frame {
    /*  0 */ uint64 ra;
    /*  8 */ uint64 sp;
    /*  16 */ uint64 gp;
    /*  24 */ uint64 tp;
    /*  32 */ uint64 t0;
    /*  40 */ uint64 t1;
    /*  48 */ uint64 t2;
    /*  56 */ uint64 s0;
    /* 64 */ uint64 s1;
    /* 72 */ uint64 a0;
    /* 80 */ uint64 a1;
    /* 88 */ uint64 a2;
    /* 96 */ uint64 a3;
    /* 104 */ uint64 a4;
    /* 112 */ uint64 a5;
    /* 120 */ uint64 a6;
    /* 128 */ uint64 a7;
    /* 136 */ uint64 s2;
    /* 144 */ uint64 s3;
    /* 152 */ uint64 s4;
    /* 160 */ uint64 s5;
    /* 168 */ uint64 s6;
    /* 176 */ uint64 s7;
    /* 184 */ uint64 s8;
    /* 192 */ uint64 s9;
    /* 200 */ uint64 s10;
    /* 208 */ uint64 s11;
    /* 216 */ uint64 t3;
    /* 224 */ uint64 t4;
    /* 232 */ uint64 t5;
    /* 240 */ uint64 t6; // 31 registradores
    // trap_stack aponta para a pilha usada pelo kernel para tratar o trap  
    /* 248 */ uint8 * trap_stack;
    /* 256 */ uint64 hartid;
    /* 264 */ uint64 epc;
};

typedef struct trap_frame TrapFrame;