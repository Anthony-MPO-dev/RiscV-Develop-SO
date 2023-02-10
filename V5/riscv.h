#include "types.h"

static inline void
w_mscratch(uint64 x){
    asm volatile("csrw mscratch, %0": :"r"(x));
}