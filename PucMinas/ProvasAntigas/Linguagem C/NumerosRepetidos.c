#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct Celula {
    int elemento;
    struct Celula* prox;
} Celula;

typedef struct Fila {
    struct Celula* primeiro;
    struct Celula* ultimo;
} Fila;

Celula* criarCelula(int elemento) {
    Celula* nova = (Celula*)malloc(sizeof(Celula));
    nova->elemento = elemento;
    nova->prox = NULL;
    return nova;
}

Fila* criarFila() {
    Fila* nova = (Fila*)malloc(sizeof(Fila));
    Celula* cabeca = criarCelula(-1);
    nova->primeiro = cabeca;
    nova->ultimo = cabeca;
    return nova;
}

void inserirFila(Fila* f, int x) {
    f->ultimo->prox = criarCelula(x);
    f->ultimo = f->ultimo->prox;
}

int main() {
    int N;
    if (scanf("%d", &N) != 1) return 0;

    Fila* f = criarFila();
    int i = 0;
    while (i < N) {
        int valor = 0;
        scanf("%d", &valor);
        inserirFila(f, valor);
        i++;
    }
    
    bool encontrouUnico = false;
    Celula* atual = f->primeiro->prox;

    while (atual != NULL) {
        int elementoAtual = atual->elemento;
        int contRepeticoes = 0;

        while (atual->prox != NULL && atual->prox->elemento == elementoAtual) {
            contRepeticoes++;
            atual = atual->prox;
        }

        if (contRepeticoes == 0) {
            if (encontrouUnico) {
                printf(" ");
            }
            printf("%d", elementoAtual);
            encontrouUnico = true;
        }

        atual = atual->prox;
    }

    if (!encontrouUnico) {
        printf("VAZIO");
    }
    printf("\n");

    return 0;
}