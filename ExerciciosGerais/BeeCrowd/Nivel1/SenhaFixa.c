#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

bool confereSenha(int valor, int senha){
    return valor == senha;
}

int main(){
    int senha = 2002;
    int tentativa;
    scanf("%d", &tentativa);
    if(confereSenha(tentativa, senha)){
        printf("Acesso Permitido\n");
    }else{
        while(!confereSenha(tentativa, senha)){
            printf("Senha Invalida\n");
            scanf("%d", &tentativa);
        }
        printf("Acesso Permitido\n");
    }
    return 0;
}