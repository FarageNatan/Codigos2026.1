#include <stdio.h>
#include <stdlib.h>

int tamanhoString(char* string){
    int tam = 0;
    while(string[tam] != '\0'){
        tam++;
    }
    return tam;
}

char* inverter(char* string, int tam){
    char* invertida = malloc((tam + 1) * sizeof(char));
    int j = 0;
    for(int i = tam - 1; i >= 0; i--){
        invertida[j] = string[i];
        j++;
    }
    return invertida;
}

int main(){
    char string[1000];
    char* invertida;
    fgets(string, sizeof(string), stdin);
    int tam = tamanhoString(string);
    if (string[tam - 1] == '\n') { //tratamento do \n quando utilizamos o fgets
        string[tam - 1] = '\0';
        tam--;
    }
    while(!(string[0] == 'F' && string[1] == 'I' && string[2] == 'M' && tam == 3)){
        invertida = inverter(string, tam);
        printf("%s\n", invertida);
        fgets(string, sizeof(string), stdin);
        tam = tamanhoString(string);
        if (string[tam - 1] == '\n') { 
            string[tam - 1] = '\0';
            tam--;
        }
    }
    return 0;
}