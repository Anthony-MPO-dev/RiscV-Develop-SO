void uartinit();
void uartputc(int c);
int uartgetc();

// printf
void printf(char *, ...);
void panic(char *);

//memória
void memory_init();

void* kalloc(int);

void kfree(void *);