#include <stdio.h>
#include <stdlib.h>

int main(){
    int quantidadeNotas = 0;
    int selecionadas = 0;
    scanf("%d %d", &quantidadeNotas, &selecionadas);

    int* notas = (int*)malloc(quantidadeNotas * sizeof(int));

    for(int i = 0; i < quantidadeNotas; i++){
        scanf("%d", &notas[i]);
    }

    for(int i = 1; i < quantidadeNotas; i++){
        int tmp = notas[i];
        int j = i - 1;
        while(j>= 0 && notas[j] > tmp){
            notas[j + 1] = notas[j];
            j--;
        }
        notas[j + 1] = tmp;
    }

    int soma = 0;
    
    int* notasSelecionadas = (int*)malloc(selecionadas * sizeof(int));

    int qtd = 0;
    for(int i = quantidadeNotas - 1; qtd < selecionadas; i--){    
        soma += notas[i];
        qtd++;
    }

    printf("%d\n", soma);
}