void uartinit();

void uartputc(int c);
int uartgetc();

// printf
void printf(char *, ...);
void panic(char *msg);

//memória
void memory_init();

void* kalloc(int);

void kfree(void *);

//plic
void plic_init();
uint32 plic_claim(void);
void plic_complete(uint32);

//console
void console_handler();