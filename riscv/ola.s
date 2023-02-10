.section .text
# Prepara parâmetros para invocar a função write (syscall)

.global _start

_start: # ponto de entrada (a 1ª instrução a ser executada)
#load imediate -> li
li a0 ,1   # saida padrão (terminal) Ex[a0 = 1;]
#load adress -> la
la a1, msg # endereço da string a ser impressa
li a2, 14   # qtd de bytes a ser impressa Ex[a2 = 14]
li a7, 64  # ID syscall write -> ID (64) == write
ecall      # Transfere controle para SO (invoca a syscall)

finaliza: # Rotulo apenas para legibilidade
li a0, 0 #  
li a7, 94 #ID syscall exit -> call exit(0) function == 94
ecall
# ...

.section .data

msg: 
.ascii "Olá mundo\n\n"
msg_fim:
#msg2: .word 234 # armazena na memoria o inteiro 234

