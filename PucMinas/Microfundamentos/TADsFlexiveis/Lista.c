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

Celula* new_celula(){
    Celula* nova = (Celula*)malloc(sizeof(Celula));
    nova->elemento = 0;
    nova->prox = NULL;
    return nova;
}

Lista* nova_lista(){
    Lista* novaLista = (Lista*) malloc(sizeof(Lista));
    Celula* sentinela = new_celula(); 
    novaLista->primeiro = novaLista->ultimo = sentinela;
    return novaLista;
}

int tamanhoLista(Lista* lista){
    int cont = 0;
    for(Celula* i = lista->primeiro; i != lista->ultimo; i = i->prox, cont++);
    return cont;
}

void inserirInicio(Lista* lista, int x){
    Celula* tmp = nova_celula(x);
    tmp->prox = lista->primeiro->prox;
    lista->primeiro->prox = tmp;     
    if(lista->primeiro == lista->ultimo){
        lista->ultimo = tmp;
    }
}

void inserirNovaCabeca(Lista* lista, int x){
    Celula* tmp = nova_celula(x);
    tmp->prox = lista->primeiro;
    lista->primeiro = tmp;
}

void inserirElementoCabeca(Lista* lista, int x){
    lista->primeiro->elemento = x;
    Celula* tmp = new_celula();
    tmp->prox = lista->primeiro;
    lista->primeiro = tmp;
}

void inserirFim(Lista* lista, int x){
    Celula* tmp = nova_celula(x);
    lista->ultimo->prox = tmp;
    lista->ultimo = tmp;
}

void inserirPos(Lista* lista, int x, int pos){
    int tamanho = tamanhoLista(lista);
    if(pos < 0 || pos > tamanho){
        printf("Erro!");
        return;
    }else if(pos == 0){
        inserirInicio(lista, x);
    }else if(pos == tamanho){
        inserirFim(lista, x);
    }else{
        Celula* i = lista->primeiro;
        for(int j = 0; j < pos; i = i->prox, j++);
        Celula* tmp = nova_celula(x);
        tmp->prox = i->prox;
        i->prox = tmp;
    }
}

int removerInicio(Lista* lista){
    if(lista->primeiro == lista->ultimo){
        printf("Lista Vazia\n");
        return 0;
    }
    Celula* tmp = lista->primeiro->prox;
    int resp = tmp->elemento;
    lista->primeiro->prox = tmp->prox;
    tmp->prox = NULL;
    tmp = NULL;
    free(tmp);
    return resp;
}

int removerFim(Lista* lista){
    if(lista->primeiro == lista->ultimo){
        printf("Lista Vazia\n");
        return 0;
    }
    int resp = lista->ultimo->elemento;
    Celula* i;
    for(i = lista->primeiro; i->prox != lista->ultimo; i = i->prox);
    lista->ultimo = i;
    i = lista->ultimo->prox = NULL;
    return resp;
}

int removerPos(Lista* lista, int pos){
    int resp, tamanho = tamanhoLista(lista);
    if(lista->primeiro == lista->ultimo){
        printf("Lista Vazia\n");
        return 0;
    }else if(pos < 0 || pos > tamanho){
        printf("Posicao invalida\n");
    }else if(pos == 0){
        resp = removerInicio(lista);
    }else if(pos == tamanho - 1){   
        resp = removerFim(lista);
    }else{
        Celula* i = lista->primeiro;
        for(int j = 0; j < pos; i = i->prox, j++);
        resp = i->prox->elemento;
        i->prox = i->prox->prox;
        i->prox->prox = NULL;
    }
    return resp;
}

void mostrar(Lista* lista){
    for(Celula* i = lista->primeiro->prox; i != NULL; i = i->prox){
        printf("%d ", i->elemento);
    }
}


int main(){
    Lista* lista = nova_lista();

    inserirInicio(lista, 10);
    inserirInicio(lista, 20);
    inserirInicio(lista, 30);
    inserirFim(lista, 40);
    inserirFim(lista, 50);
    //int resp = removerInicio(lista);
    //printf("%d\n", resp);
    //resp = removerInicio(lista);
    //printf("%d\n", resp);
    int resp = removerFim(lista);
    printf("%d\n", resp);
    resp = removerPos(lista, 3);
    printf("%d\n", resp);
    
    mostrar(lista);

    free(lista);
    return 0;
}