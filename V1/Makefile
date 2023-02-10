PRE = riscv64-linux-gnu-
CC = $(PRE)gcc #riscv64-linux-gnu-gcc
LD = $(PRE)ld #riscv64-linux-gnu-ld

CFLAGS += -ffreestanding   # Não ha SO no ambiente de execução (Ambiente sem bibliotecas padrão fornecidas pelo SO)
CFLAGS += -march=rv64gc    # Arquitetura RISC-V de 64 bits 
CFLAGS += -mabi=lp64       # Tipos longos e ponteiros são de 64 bits. Inteiros são de 32 bits
CFLAGS += -Wall            # Aumenta as Mensagens de warning - deixa a verificação mais precisa para apontar erros
CFLAGS += -g               # Gera informações extra p/ depuração
CFLAGS += -O0              # Otimiza o código o mínimo possivel
CFLAGS += -c               # Compila mas não invoca o linker

LDFLAGS += -Tkernel.ld # Script para o linker
LDFLAGS += -nostdlib  # Não vincula funções de terceiros

#EMULADOR
QEMU = qemu-system-riscv64 
GRAPI = -append 'console=ttyS0'  -nographic -serial mon:stdio #Remove tudos os graficos do SO, 

OBJ = \
	boot.o \
	main.o \
	uart.o


kernel: $(OBJ)
	$(LD) $(LDFLAGS) -o $@ $(OBJ)
# $@ pega a variavel de saida o kernel 
# $< pega as variaveis de entrada ou seja OBJ


run: kernel 
	$(QEMU) $(GRAPI) -smp 4 -machine virt -bios none -kernel $<

#automatiza compilação de  arquivos .c
%.o: %.c 
	$(CC) $(CFLAGS) $< 
#automatiza compilação de  arquivos .s
%.o: %.s 
	$(CC) $(CFLAGS) $< 



# main.o: main.c
#	$(CC) $(CFLAGS) main.c #riscv64-linux-gnu-gcc -ffreestanding -march=rv64gc -mabi=lp64 -Wall -g -O0 -c main.c
#boot.o: boot.s
#	$(CC) $(CFLAGS) boot.s
# uart.o: uart.c
#	$(CC) $(CFLAGS)



clean:
	rm -f $(OBJ) kernel

