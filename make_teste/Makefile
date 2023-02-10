	#o simbolo @ esconde no 
	#terminal o codigo que  
	#esta sendo executado

adeus: ola
	@echo "2ª regra a ser executada <adeus>"
	@echo "Adeus mundo"

ola:
	@echo "1ª regra a ser executada <ola>"
	@echo "Hoje é `date`"
	@touch ola

hoje:
	@echo "Hoje é `date`" > hoje.txt

arquivos := arq1 arq2

arq0:$(arquivos)
	@echo "Criando arquivo arq0"
	@touch arq0

arq1:
	@echo "Criando arquivo arq1"
	@touch arq1

arq2:
	@echo "Criando arquivo arq2"
	@touch arq2

clean:
	@rm -f arq0 arq1 arq2

clean2:
	@rm -f arq0 arq1 arq2 ola hoje.txt


um:
	@touch um

dois: 
	@touch dois

tres:
	@touch tres

#Uma regra com multiplos pré-requisitos
tudo: um dois tres
#Sem uma receita

#Multiplas regras e uma mesma receita e pré-requisitos

all: f1.o f2.o

f1.o f2.o:
	echo $@  #'@' é o nome do target(alvo) da regra
# equivalente a:

#f1.o:
#	echo f1.0

#f2.o:
#	echo f2.0