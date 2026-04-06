#include <stdio.h>
#include <stdlib.h>
#define TAM 100


typedef struct
{
    int dados[TAM];
    int tamanho;    
}Lista;

void inicializarLista(Lista* lista){
    lista->tamanho = 0;
}

void inserirInicio(Lista* lista, int x){
    if(lista->tamanho != TAM){
        for(int i = lista->tamanho - 1; i >= 0; i--){
            lista->dados[i + 1] = lista->dados[i];
        }
        lista->dados[0] = x;
        lista->tamanho++;
    }else{
        printf("Lista Cheia");
    }
}

int removerInicio(Lista* lista){
    int resp;
    if(lista->tamanho == 0){
        printf("Lista Vazia");
        resp = 0;
    }else{
        resp = lista->dados[0];
        for(int i = 0; i < lista->tamanho; i++){
            lista->dados[i] = lista->dados[i + 1];
        }
        lista->tamanho--;
    }
    return resp;
}

int removerPosicao(Lista* lista, int pos){
    int resp;
    if(lista->tamanho == 0 || pos > lista->tamanho || pos < 0){
        printf("Erro");
    }else{
        resp = lista->dados[pos];
        for(int i = pos; i < lista->tamanho - 1; i++){
            lista->dados[i] = lista->dados[i + 1];
        }
        lista->tamanho--;
    }
    return resp;
}

void imprimirLista(Lista *l) {
    printf("Lista: [ ");
    for(int i = 0; i < l->tamanho; i++) {
        printf("%d ", l->dados[i]);
    }
    printf("]  Tamanho: %d\n", l->tamanho);
}

int main(){
    Lista minhaLista;
    inicializarLista(&minhaLista);

    inserirInicio(&minhaLista, 10);
    inserirInicio(&minhaLista, 20);
    inserirInicio(&minhaLista, 30);

    imprimirLista(&minhaLista);          

    printf("Removido do inicio: %d\n", removerInicio(&minhaLista));
    imprimirLista(&minhaLista);          

    printf("Removido da pos 1: %d\n", removerPosicao(&minhaLista, 1));
    imprimirLista(&minhaLista);   
    return 0;
}