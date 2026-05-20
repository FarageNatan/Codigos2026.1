#include <stdio.h>
#include <stdlib.h>

typedef struct Camisa {
    char aluno[100];
    char tamanho;
    char cor[50];
} Camisa;

/* ── Aloca e inicializa uma nova Camisa ── */
Camisa* novaCamisa() {
    Camisa* nova = (Camisa*)malloc(sizeof(Camisa));
    if (nova == NULL) return NULL;
    nova->aluno[0] = '\0';
    nova->tamanho  = '\0';
    nova->cor[0]   = '\0';
    return nova;
}

/* ── Copia string sem string.h ── */
char* copiaString(char* string) {
    int tamanho = 0;
    while (string[tamanho] != '\0') tamanho++;

    char* copia = (char*)malloc((tamanho + 1) * sizeof(char));
    if (copia == NULL) return NULL;

    int i = 0;
    while (string[i] != '\0') {
        copia[i] = string[i];
        i++;
    }
    copia[i] = '\0';
    return copia;
}

/* ── Compara duas strings sem string.h ── */
int comparaStrings(char* a, char* b) {
    int i = 0;
    while (a[i] != '\0' && b[i] != '\0') {
        if (a[i] != b[i])
            return a[i] - b[i];
        i++;
    }
    return a[i] - b[i];
}

/* ── Converte tamanho para número (para ordenar descendente) ──
   G=1, M=2, P=3 → assim G vem primeiro quando ordenamos ascendente por esse número */
int ordemTamanho(char t) {
    if (t == 'G') return 1;
    if (t == 'M') return 2;
    if (t == 'P') return 3;
    return 4;
}

/* ── Compara duas camisas pelos 3 critérios ── */
int comparaCamisas(Camisa* a, Camisa* b) {
    // 1º: cor ascendente
    int cmpCor = comparaStrings(a->cor, b->cor);
    if (cmpCor != 0) return cmpCor;

    // 2º: tamanho DESCENDENTE (G > M > P)
    int cmpTamanho = ordemTamanho(a->tamanho) - ordemTamanho(b->tamanho);
    if (cmpTamanho != 0) return cmpTamanho;

    // 3º: nome ascendente
    return comparaStrings(a->aluno, b->aluno);
}

/* ── Insertion Sort por ponteiros de Camisa ── */
void insertionSort(Camisa** camisas, int C) {
    for (int i = 1; i < C; i++) {
        Camisa* tmp = camisas[i];
        int j = i - 1;
        while (j >= 0 && comparaCamisas(camisas[j], tmp) > 0) {
            camisas[j + 1] = camisas[j];
            j--;
        }
        camisas[j + 1] = tmp;
    }
}

int main() {
    int C;
    scanf("%d", &C);

    int primeiroCaso = 1;

    while (C != 0) {
        Camisa** camisas = malloc(C * sizeof(Camisa*));
        for (int i = 0; i < C; i++) {
            camisas[i] = novaCamisa();
        }

        for (int j = 0; j < C; j++) {
            scanf(" %[^\n]", camisas[j]->aluno);
            scanf(" %s",     camisas[j]->cor);
            scanf(" %c",    &camisas[j]->tamanho);
        }

        insertionSort(camisas, C);

        if (!primeiroCaso) printf("\n");
        primeiroCaso = 0;

        for (int j = 0; j < C; j++) {
            printf("%s %c %s\n", camisas[j]->cor,
                                 camisas[j]->tamanho,
                                 camisas[j]->aluno);
        }

        // Libera memória
        for (int i = 0; i < C; i++) free(camisas[i]);
        free(camisas);

        scanf("%d", &C);
    }

    return 0;
}