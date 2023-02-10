#include "types.h"

static inline void
w_mscratch(uint64 x){
    asm volatile("csrw mscratch, %0": :"r"(x));
}

static inline void
w_mtvec(uint64 x){
    asm volatile("csrw mtvec, %0": :"r"(x));
}

static inline void
w_mstatus(uint64 x){
    asm volatile("csrw mstatus, %0": :"r"(x));
}

static inline uint64 
r_mstatus(){
    uint64 x;
    asm volatile("csrr %0, mstatus":"=r" (x));
    return x;
}

static inline void
w_mepc(uint64 x){
    asm volatile("csrw mepc, %0": :"r" (x));
}

