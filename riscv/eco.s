.section .text
# Prepara parâmetros para invocar a função write (syscall)

.global _start

_start: # ponto de entrada (a 1ª instrução a ser executada)

li a0, 0
la a1, buffer
li a2, 50
li a7, 63
ecall


li a0 ,1
la a1, buffer
li a2, 50   
li a7, 64  
ecall      # Transfere controle para SO (invoca a syscall)

li a0 ,1   # saida padrão (terminal) Ex[a0 = 1;]
#load adress -> la
la a1, msg # endereço da string a ser impressa
li a2, 2   # qtd de bytes a ser impressa Ex[a2 = 4]
li a7, 64  # ID syscall write -> ID (64) == write
ecall      # Transfere controle para SO (invoca a syscall)


finaliza: # Rotulo apenas para legibilidade
li a0, 0 #  
li a7, 94 #ID syscall exit -> call exit(0) function == 94
ecall
# ...


.section .bss
buffer: .space  51
.section .data
msg: 
.ascii "\n\n"

