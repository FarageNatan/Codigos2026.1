#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct {
    int* array;
    int primeiro, ultimo, capacidade;
}Fila;

Fila* criarFila(){
    return criarFilaComTamanho(5);
}

Fila* criarFilaComTamanho(int tam){
    Fila* fila = (Fila*)malloc(sizeof(Fila));
    fila->capacidade = tam + 1;
    fila->primeiro = 0;
    fila->ultimo = 0;
    return fila;
}

bool estaVazia(Fila* fila){
    return fila->primeiro == fila->ultimo;
}

bool estaCheia(Fila* fila){
    return (fila->ultimo + 1) % fila->capacidade == fila->primeiro;
}

void inserir(Fila* f, int x) {
    if (estaCheia(f)) {
        printf("Erro: Fila cheia!\n");
        return;
    }
    f->array[f->ultimo] = x;
    f->ultimo = (f->ultimo + 1) % f->capacidade;   // volta para 0 quando chega no final
}

// Remover elemento (dequeue)
int remover(Fila* f) {
    if (estaVazia(f)) {
        printf("Erro: Fila vazia!\n");
        return -1;
    }
    int valor = f->array[f->primeiro];
    f->primeiro = (f->primeiro + 1) % f->capacidade;
    return valor;
}

void mostrar(Fila* f) {
    if (estaVazia(f)) {
        printf("Fila vazia!\n");
        return;
    }
    
    printf("Fila: [ ");
    int i = f->primeiro;
    
    while (i != f->ultimo) {
        printf("%d ", f->array[i]);
        i = (i + 1) % f->capacidade;
    }
    printf("]  primeiro=%d | ultimo=%d | capacidade=%d\n", 
           f->primeiro, f->ultimo, f->capacidade);
}

void destruirFila(Fila* f) {
    if (f != NULL) {
        free(f->array);
        free(f);
    }
}

int main(){
    Fila* minhaFila = criarFila();

    inserir(minhaFila, 10);
    inserir(minhaFila, 20);
    inserir(minhaFila, 30);
    inserir(minhaFila, 40);
    inserir(minhaFila, 50);   

    mostrar(minhaFila);

    printf("Removido: %d\n", remover(minhaFila));
    printf("Removido: %d\n", remover(minhaFila));

    inserir(minhaFila, 60);
    inserir(minhaFila, 70);

    mostrar(minhaFila);

    // Tentativa de inserir quando cheia
    inserir(minhaFila, 99);

    destruirFila(minhaFila);
    return 0;
}