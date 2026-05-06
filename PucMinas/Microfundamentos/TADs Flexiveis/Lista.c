#include <stdio.h>
#include <stdlib.h>

typedef struct Celula
{
    int elemento;
    struct Celula* prox;
}Celula;

typedef struct Lista
{
    Celula* primeiro;
    Celula* ultimo;
}Lista;

Celula* nova_celula(int x){
    Celula* nova = (Celula*)malloc(sizeof(Celula));
    nova->elemento = x;
    nova->prox = NULL;
    return nova;
}

void inserirInicio(Lista* lista, int x){
    Celula* tmp = nova_celula(x);
    tmp->prox = lista->primeiro->prox;
    lista->primeiro->prox = tmp;     
    if(lista->primeiro == lista->ultimo){
        lista->ultimo = tmp;
    }
    free(tmp);
}

void inserirNovaCabeca(Lista* lista, int x){
    Celula* tmp = nova_celula(x);
    tmp->prox = lista->primeiro;
    lista->primeiro = tmp;
    free(tmp);
}

void inserirFim(Lista* lista, int x){
    Celula* tmp = nova_celula(x);
    lista->ultimo->prox = tmp;
    lista->ultimo = tmp;
    free(tmp);
}

int main(){




    return 0;
}