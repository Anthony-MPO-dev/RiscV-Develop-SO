void uartinit();
void uartputc(int c);
int uartgetc();

// printf
void printf(char *, ...);

//memória
void memory_init();

void* kalloc(int);

void kfree(void *);