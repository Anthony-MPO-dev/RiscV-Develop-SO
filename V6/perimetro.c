#include <stdarg.h>

int perimetro(int lados, ...){ // ... -> variadics (parametros variados) 
    
    int i = 0;
    int soma = 0;

    va_list ap; // ponteiro p/ a lista de argumentos variados
    
    // ap aponta p/ 1º argumento da lista
    va_start(ap, lados); // Inicializa ponteiro


    for(i = 0; i< lados; i++){
        //obtem argumento variavel de lado e adiciona a soma do perimetro
        soma += va_arg(ap, int);
    }

    return soma;
}