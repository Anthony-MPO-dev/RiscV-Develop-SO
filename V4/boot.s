.global _start
#.equ STACK_SIZE, 4096

  #codigo vai ser executado em todos os cores ao mesmo tempo 
_start:
    #Control and set resgister - csrr
    csrr t0, mhartid # pega mhartid(Registrador especial) e joga dentro de t0  
    bnez t0, park # salta se não igual a zero
    # la -> load adress
    la sp, stack_end # carrega sp com endereço stack_end
    #li sp, 0x1000;
    j entry # função em C

    #Coloca demais cores em espera
park:
    wfi #Wait for interruption(espera por interrupção)
    j park # se interrupção volta à espera

#.skip STACK_SIZE #Diretiva informando para saltar 4096 bits na memoria 
#stack_end:
        