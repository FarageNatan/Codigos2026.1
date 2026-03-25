#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int tamanhoString(char* placa){
    int tam = 0;
    while(placa[tam] != '\0'){
        tam++;
    }
    return tam;
}

bool placaAntiga(char* placa, int tam){
    bool ehAntiga = true;
    if(tam != 7){
        ehAntiga = false;
    } else {
        for(int i = 0; i < 3; i++){
            if(!(placa[i] >= 'A' && placa[i] <= 'Z')){
                ehAntiga = false;
                i = 3;
            }
        }
        for(int j = 3; j < tam; j++){
            if(!(placa[j] >= '0' && placa[j] <= '9')){
                ehAntiga = false;
                j = tam;
            }
        }
    }
    return ehAntiga;
}

bool placaNova(char* placa, int tam){
    bool ehNova = true;
    if(tam != 7){
        ehNova = false;
    } else {
        for(int i = 0; i < 3; i++){
            if(!(placa[i] >= 'A' && placa[i] <= 'Z')){
                ehNova = false;
            }
        }
        if(!(placa[3] >= '0' && placa[3] <= '9')){
            ehNova = false;
        }
        if(!(placa[4] >= 'A' && placa[4] <= 'Z')){
            ehNova = false;
        }
        if(!(placa[5] >= '0' && placa[5] <= '9')){
            ehNova = false;
        }
        if(!(placa[6] >= '0' && placa[6] <= '9')){
            ehNova = false;
        }
    }
    return ehNova;
}

int main(){
    int quantidade = 0;
    scanf("%d", &quantidade);
    int i = 0;
    while(i < quantidade){
        char placa[100];
        scanf(" %[^\n]", placa);
        int tam = tamanhoString(placa);
        
        bool nova = placaNova(placa, tam);
        bool antiga = placaAntiga(placa, tam);

        if(nova){
            printf("M\n");
        }else if(antiga){
            printf("A\n");
        }else{
            printf("I\n");
        }
        i++;
    }
    return 0;
}
