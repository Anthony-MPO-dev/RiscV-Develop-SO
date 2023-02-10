somamain.x: soma.o somamain.o
	@echo "Compilado com sucesso\nGerando somamain.x"
	@riscv64-linux-gnu-gcc -static soma.o somamain.o -o somamain.x 

soma.o: soma.s
	@echo "Compilando soma.s"
	@riscv64-linux-gnu-gcc -c soma.s -o soma.o

somamain.o: somamain.c
	@echo "Compilando somamain.c"
	@riscv64-linux-gnu-gcc -c somamain.c -o somamain.o 

run: somamain.x
	@echo "Running..."
	@~/Documentos/riscv/spike-sim/spike -m128 ~/Documentos/riscv/spike-sim/pk somamain.x
	



clean:
	@rm -f somamain.o soma.o somamain.x
	