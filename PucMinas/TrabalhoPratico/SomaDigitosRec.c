#include <stdio.h>
#include <stdlib.h>

int tamanhoString(char* string){
    int tam = 0;
    while(string[tam] != '\0'){
        tam++;
    }
    return tam;
}

int somaDigitos(int numero){
    int resp = 0;
    if(numero > 0){
        resp = (numero % 10 + somaDigitos(numero / 10));
    }
    return resp;
}

int transformaNumero(char* string){
    int num = 0;
    
    for (int i = 0; string[i] != '\0'; i++) {
        if (string[i] >= '0' && string[i] <= '9') {
            num = num * 10 + (string[i] - '0');
        }
    }

    return num;
}

int main(){
    char* numero = malloc(1000 * sizeof(char));
    fgets(numero, 1000, stdin);
    int tam = tamanhoString(numero);
    if (tam > 0 && numero[tam - 1] == '\n') {
        numero[tam - 1] = '\0';
        tam--;
    }
    while(numero != EOF){
        int num = transformaNumero(numero);
        int soma = somaDigitos(num);
        printf("%d\n", soma);

        fgets(numero, 1000, stdin);
        tam = tamanhoString(numero);
        if (tam > 0 && numero[tam - 1] == '\n') {
            numero[tam - 1] = '\0';
            tam--;
        }
    }

    free(numero);
    return 0;   
}