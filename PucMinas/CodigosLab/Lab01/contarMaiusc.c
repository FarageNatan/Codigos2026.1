#include <stdio.h>
#include <stdlib.h>

int tamString(char* s){
    int cont = 0;
    while(s[cont] != '\0'){
        cont++;
    }
    return cont;
}

static int maiuscIte(char* s, int pos){
    int length = tamString(s), cont = 0;
    for(int i = pos; i < length; i++){
        if(s[i] >= 'A' && s[i] <= 'Z'){
            cont++;
        }
    }
    return cont;
}

int gatilho(char* s){
    return maiuscIte(s, 0);
}

static int contarMaiusc(char* s, int pos){
    int length = tamString(s);
    int cont = 0;
    if(pos < length){
        if(s[pos] >= 'A' && s[pos] <= 'Z'){
            cont = 1 + contarMaiusc(s, pos + 1);
        }else{
            cont = contarMaiusc(s, pos + 1);
        }
    }
    return cont;
}

static int contarRec(char* s){
    return contarMaiusc(s, 0);
}

int main(){
    char nome[50];
    scanf("%[^\n]", nome);
    int quantidade = contarRec(nome);
    printf("%d", quantidade);
    return 0;
}