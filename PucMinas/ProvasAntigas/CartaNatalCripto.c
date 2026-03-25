#include <stdlib.h>
#include <stdio.h>

int tamanhoString(char* array){
    int tam = 0;
    while(array[tam] != '\0'){
        tam++;
    }
    return tam;
}

void reescreverFrase(char* string, int tam){
    for(int i = 0; i < tam; i++){
        if(string[i] == '@'){
            string[i] = 'a';
        } else if(string[i] == '&'){
            string[i] = 'e';
        } else if(string[i] == '!'){
            string[i] = 'i';
        } else if(string[i] == '*'){
            string[i] = 'o';
        } else if(string[i] == '#'){
            string[i] = 'u';
        } else {
            string[i] = string[i];
        }
    }
}


int main(){
    char string[1000];
        int tam = tamanhoString(string);
        reescreverFrase(string, tam);
        printf("%s", string);
    return 0;
}