#include <stdio.h>
#include <stdlib.h>

int main(){
    float nota = 0, soma = 0, cont = 0;
    while(cont < 2){
        scanf("%f", &nota);
        if(nota > -1 && nota < 11){
            soma += nota;
            cont++;
        }else{
            printf("nota invalida\n");
        }
    }
    float media = soma / cont;
    printf("media = %.2f\n", media);

    return 0;
}