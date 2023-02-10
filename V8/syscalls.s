 #Código assembly é necessário para:
 #carrega o registrador a7 com o ID da syscall
 #executar a instrução ecall (que causa a exceção)
.global msg_syscall
msg_syscall:
    li a7, 1
    ecall
    ret

.global set_hostname
set_hostname:
    li a7, 2
    ecall
    ret

.global halt
halt:
    li a7, 3
    ecall
    ret