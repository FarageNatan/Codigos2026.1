#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define TAM_LINHA 1024
#define MAX_REGISTROS 1000

// --- Estruturas ---

typedef struct {
    int ano, mes, dia;
} Data;

typedef struct {
    int hora, minuto;
} Hora;

typedef struct {
    int id;
    char nome[100];
    char cidade[100];
    int capacidade;
    double avaliacao;
    char tiposCozinha[10][50];
    int numTipos;
    int faixaPreco;
    Hora abertura;
    Hora fechamento;
    Data dataAbertura;
    bool aberto;
} Restaurante;

// --- Funções de Data e Hora ---

Data parseData(char *s) {
    Data d = {0, 0, 0};
    if (s) sscanf(s, "%d-%d-%d", &d.ano, &d.mes, &d.dia);
    return d;
}

Hora parseHora(char *s) {
    Hora h = {0, 0};
    if (s) sscanf(s, "%d:%d", &h.hora, &h.minuto);
    return h;
}

int converteFaixaPreco(char *s) {
    int count = 0, i = 0;
    while (s[i] != '\0') {
        if (s[i] == '$') count++;
        i++;
    }
    return count;
}

// --- Parsing do CSV ---

// Copia manualmente os campos separados por vírgula, respeitando aspas
int parseCampos(char *linha, char campos[][200], int maxCampos) {
    int idx_campos = 0;
    int idx_buffer = 0;
    int dentro_aspas = 0;
    int i = 0;

    while (linha[i] != '\0' && idx_campos < maxCampos) {
        if (linha[i] == '"') {
            dentro_aspas = !dentro_aspas;
        } else if (linha[i] == ',' && !dentro_aspas) {
            campos[idx_campos][idx_buffer] = '\0';
            idx_campos++;
            idx_buffer = 0;
        } else {
            campos[idx_campos][idx_buffer++] = linha[i];
        }
        i++;
    }

    // Último campo
    campos[idx_campos][idx_buffer] = '\0';
    // Remove \r\n do último campo
    int j = 0;
    while (campos[idx_campos][j] != '\0' && campos[idx_campos][j] != '\r' && campos[idx_campos][j] != '\n') j++;
    campos[idx_campos][j] = '\0';
    idx_campos++;

    return idx_campos;
}

// Separa tipos de cozinha pelo separador ';'
int parseLista(char *str, char lista[][50], int maxItens) {
    int n = 0, pos = 0, i = 0;

    while (str[i] != '\0' && n < maxItens) {
        if (str[i] == ';') {
            lista[n][pos] = '\0';
            n++;
            pos = 0;
        } else {
            lista[n][pos++] = str[i];
        }
        i++;
    }
    lista[n][pos] = '\0';
    return n + 1;
}

int lerRestaurante(char *linha, Restaurante *r) {
    char campos[12][200];
    int total = parseCampos(linha, campos, 12);
    if (total < 10) return 0;

    char aberturaStr[10], fechamentoStr[10];
    sscanf(campos[7], "%[^-]-%s", aberturaStr, fechamentoStr);

    sscanf(campos[0], "%d", &r->id);
    sscanf(campos[1], "%99[^\n]", r->nome);
    sscanf(campos[2], "%99[^\n]", r->cidade);
    sscanf(campos[3], "%d", &r->capacidade);
    sscanf(campos[4], "%lf", &r->avaliacao);
    r->numTipos    = parseLista(campos[5], r->tiposCozinha, 10);
    r->faixaPreco  = converteFaixaPreco(campos[6]);
    r->abertura    = parseHora(aberturaStr);
    r->fechamento  = parseHora(fechamentoStr);
    r->dataAbertura = parseData(campos[8]);
    r->aberto      = (strcmp(campos[9], "true") == 0);

    return 1;
}

// --- Impressão ---

void formatarRestaurante(Restaurante *r) {
    char hAbertura[10], hFechamento[10], dLancamento[15], precoStr[10], tiposStr[500];
    int i, offset = 0;

    sprintf(hAbertura,   "%02d:%02d", r->abertura.hora,   r->abertura.minuto);
    sprintf(hFechamento, "%02d:%02d", r->fechamento.hora, r->fechamento.minuto);
    sprintf(dLancamento, "%02d/%02d/%04d", r->dataAbertura.dia, r->dataAbertura.mes, r->dataAbertura.ano);

    for (i = 0; i < r->faixaPreco && i < 9; i++) precoStr[i] = '$';
    precoStr[i] = '\0';

    offset += sprintf(tiposStr + offset, "[");
    for (i = 0; i < r->numTipos; i++) {
        if (i > 0) offset += sprintf(tiposStr + offset, ",");
        offset += sprintf(tiposStr + offset, "%s", r->tiposCozinha[i]);
    }
    sprintf(tiposStr + offset, "]");

    printf("[%d ## %s ## %s ## %d ## %.1f ## %s ## %s ## %s-%s ## %s ## %s]\n",
           r->id, r->nome, r->cidade, r->capacidade, r->avaliacao,
           tiposStr, precoStr, hAbertura, hFechamento, dLancamento,
           r->aberto ? "true" : "false");
}

void ordenarPorNome(Restaurante lista[], int total) {
    int i, j, minIdx;
    Restaurante temp;

    for (i = 0; i < total - 1; i++) {
        minIdx = i;
        for (j = i + 1; j < total; j++) {
            if (strcmp(lista[j].nome, lista[minIdx].nome) < 0) {
                minIdx = j;
            }
        }
        if (minIdx != i) {
            temp = lista[i];
            lista[i] = lista[minIdx];
            lista[minIdx] = temp;
        }
    }
}

int buscaBinaria(Restaurante lista[], int total, char *nome) {
    int inicio = 0, fim = total - 1;

    while (inicio <= fim) {
        int meio = (inicio + fim) / 2;
        int cmp = strcmp(lista[meio].nome, nome);

        if (cmp == 0) {
            return meio;
        } else if (cmp < 0) {
            inicio = meio + 1;
        } else {
            fim = meio - 1;
        }
    }

    return -1;
}

int compararRestaurante(Restaurante *a, Restaurante *b) {
    if (a->avaliacao < b->avaliacao) return -1;
    if (a->avaliacao > b->avaliacao) return 1;
    // Empate: ordena por nome
    return strcmp(a->nome, b->nome);
}

int particionar(Restaurante lista[], int inicio, int fim) {
    Restaurante pivo = lista[fim];
    int i = inicio - 1;

    for (int j = inicio; j < fim; j++) {
        if (compararRestaurante(&lista[j], &pivo) <= 0) {
            i++;
            Restaurante temp = lista[i];
            lista[i] = lista[j];
            lista[j] = temp;
        }
    }

    Restaurante temp = lista[i + 1];
    lista[i + 1] = lista[fim];
    lista[fim] = temp;

    return i + 1;
}

void quicksort(Restaurante lista[], int inicio, int fim) {
    if (inicio < fim) {
        int pivo = particionar(lista, inicio, fim);
        quicksort(lista, inicio, pivo - 1);
        quicksort(lista, pivo + 1, fim);
    }
}

void countingSort(Restaurante lista[], int total) {
    // Encontra o maior e menor valor de capacidade
    int minCap = lista[0].capacidade;
    int maxCap = lista[0].capacidade;

    for (int i = 1; i < total; i++) {
        if (lista[i].capacidade < minCap) minCap = lista[i].capacidade;
        if (lista[i].capacidade > maxCap) maxCap = lista[i].capacidade;
    }

    int intervalo = maxCap - minCap + 1;

    // Conta as ocorrências de cada capacidade
    int *contagem = (int *)malloc(intervalo * sizeof(int));
    for (int i = 0; i < intervalo; i++) contagem[i] = 0;
    for (int i = 0; i < total; i++) contagem[lista[i].capacidade - minCap]++;

    // Acumula as contagens
    for (int i = 1; i < intervalo; i++) contagem[i] += contagem[i - 1];

    // Monta o array de saída
    Restaurante saida[MAX_REGISTROS];
    for (int i = total - 1; i >= 0; i--) {
        int pos = contagem[lista[i].capacidade - minCap] - 1;
        saida[pos] = lista[i];
        contagem[lista[i].capacidade - minCap]--;
    }

    // Copia de volta para a lista original
    for (int i = 0; i < total; i++) lista[i] = saida[i];
    
    free(contagem);
}

// --- Pilha ---

typedef struct {
    Restaurante dados[MAX_REGISTROS];
    int topo;
} Pilha;

void inicializarPilha(Pilha *p) {
    p->topo = -1;
}

int pilhaVazia(Pilha *p) {
    return p->topo == -1;
}

void empilhar(Pilha *p, Restaurante r) {
    if (p->topo < MAX_REGISTROS - 1) {
        p->dados[++p->topo] = r;
    }
}

Restaurante desempilhar(Pilha *p) {
    return p->dados[p->topo--];
}

void insertionSortParcial(Restaurante lista[], int total, int k) {
    for (int i = 1; i < total; i++) {
        Restaurante chave = lista[i];
        int j = i - 1;

        if (i < k || strcmp(chave.cidade, lista[k-1].cidade) < 0) {
            int limite = i < k ? i : k - 1;
            j = limite - 1;

            while (j >= 0 && strcmp(lista[j].cidade, chave.cidade) > 0) {
                lista[j + 1] = lista[j];
                j--;
            }
            lista[j + 1] = chave;
        }
    }
}

int compararData(Data a, Data b) {
    if (a.ano != b.ano) return a.ano - b.ano;
    if (a.mes != b.mes) return a.mes - b.mes;
    return a.dia - b.dia;
}

int compararHeap(Restaurante *a, Restaurante *b) {
    int cmp = compararData(a->dataAbertura, b->dataAbertura);
    if (cmp != 0) return cmp;
    return strcmp(a->nome, b->nome);
}

void heapificar(Restaurante heap[], int total, int i) {
    int menor = i;
    int esq = 2 * i + 1;
    int dir = 2 * i + 2;

    if (esq < total && compararHeap(&heap[esq], &heap[menor]) < 0)
        menor = esq;
    if (dir < total && compararHeap(&heap[dir], &heap[menor]) < 0)
        menor = dir;

    if (menor != i) {
        Restaurante temp = heap[i];
        heap[i] = heap[menor];
        heap[menor] = temp;
        heapificar(heap, total, menor);
    }
}

void construirHeap(Restaurante heap[], int total) {
    for (int i = total / 2 - 1; i >= 0; i--)
        heapificar(heap, total, i);
}

Restaurante extrairMinimo(Restaurante heap[], int *total) {
    Restaurante min = heap[0];
    heap[0] = heap[--(*total)];
    heapificar(heap, *total, 0);
    return min;
}

typedef struct {
    Restaurante *dados;
    int tamanho;
    int capacidade;
} Lista;

void inicializarLista(Lista *l) {
    l->capacidade = 10;
    l->tamanho = 0;
    l->dados = (Restaurante *)malloc(l->capacidade * sizeof(Restaurante));
}

void expandirLista(Lista *l) {
    if (l->tamanho >= l->capacidade) {
        l->capacidade *= 2;
        l->dados = (Restaurante *)realloc(l->dados, l->capacidade * sizeof(Restaurante));
    }
}

void inserirInicio(Lista *l, Restaurante r) {
    expandirLista(l);
    for (int i = l->tamanho; i > 0; i--)
        l->dados[i] = l->dados[i - 1];
    l->dados[0] = r;
    l->tamanho++;
}

void inserir(Lista *l, Restaurante r, int posicao) {
    if (posicao < 0 || posicao > l->tamanho) return;
    expandirLista(l);
    for (int i = l->tamanho; i > posicao; i--)
        l->dados[i] = l->dados[i - 1];
    l->dados[posicao] = r;
    l->tamanho++;
}

void inserirFim(Lista *l, Restaurante r) {
    expandirLista(l);
    l->dados[l->tamanho++] = r;
}

Restaurante removerInicio(Lista *l) {
    Restaurante r = l->dados[0];
    for (int i = 0; i < l->tamanho - 1; i++)
        l->dados[i] = l->dados[i + 1];
    l->tamanho--;
    return r;
}

Restaurante removerPosicao(Lista *l, int posicao) {
    Restaurante r = l->dados[posicao];
    for (int i = posicao; i < l->tamanho - 1; i++)
        l->dados[i] = l->dados[i + 1];
    l->tamanho--;
    return r;
}

Restaurante removerFim(Lista *l) {
    return l->dados[--l->tamanho];
}

typedef struct No {
    Restaurante dado;
    struct No *proximo;
} No;

typedef struct {
    No *inicio;
    No *fim;
    int tamanho;
} Fila;

void inicializarFila(Fila *f) {
    f->inicio = NULL;
    f->fim = NULL;
    f->tamanho = 0;
}

int filaVazia(Fila *f) {
    return f->inicio == NULL;
}

void enfileirar(Fila *f, Restaurante r) {
    No *novo = (No *)malloc(sizeof(No));
    novo->dado = r;
    novo->proximo = NULL;

    if (filaVazia(f)) {
        f->inicio = novo;
        f->fim = novo;
    } else {
        f->fim->proximo = novo;
        f->fim = novo;
    }
    f->tamanho++;
}

Restaurante desenfileirar(Fila *f) {
    No *temp = f->inicio;
    Restaurante r = temp->dado;
    f->inicio = f->inicio->proximo;
    if (f->inicio == NULL) f->fim = NULL;
    free(temp);
    f->tamanho--;
    return r;
}

typedef struct NoFlex {
    Restaurante dado;
    struct NoFlex *proximo;
} NoFlex;

typedef struct {
    NoFlex *inicio;
    int tamanho;
} ListaEncadeada;

void inicializarListaEnc(ListaEncadeada *l) {
    l->inicio = NULL;
    l->tamanho = 0;
}

void inserirFimEnc(ListaEncadeada *l, Restaurante r) {
    NoFlex *novo = (NoFlex *)malloc(sizeof(NoFlex));
    novo->dado = r;
    novo->proximo = NULL;

    if (l->inicio == NULL) {
        l->inicio = novo;
    } else {
        NoFlex *atual = l->inicio;
        while (atual->proximo != NULL)
            atual = atual->proximo;
        atual->proximo = novo;
    }
    l->tamanho++;
}

// Selection sort: troca apenas os dados, sem remanejar ponteiros
void selectionSortEnc(ListaEncadeada *l) {
    NoFlex *i = l->inicio;

    while (i != NULL) {
        NoFlex *minNo = i;
        NoFlex *j = i->proximo;

        // Encontra o menor nome a partir de i
        while (j != NULL) {
            if (strcmp(j->dado.nome, minNo->dado.nome) < 0)
                minNo = j;
            j = j->proximo;
        }

        // Troca os dados entre i e minNo
        if (minNo != i) {
            Restaurante temp = i->dado;
            i->dado = minNo->dado;
            minNo->dado = temp;
        }

        i = i->proximo;
    }
}

int main() {
    FILE *arquivo = fopen("/tmp/restaurantes.csv", "r");
    //FILE *arquivo = fopen("../dataset/restaurantes.csv", "r");
    if (!arquivo) {
        printf("Erro ao abrir o arquivo\n");
        return 1;
    }

    Restaurante todos[MAX_REGISTROS];
    //Restaurante lista[MAX_REGISTROS];
    int total = 0;
    char linha[TAM_LINHA];

    fgets(linha, TAM_LINHA, arquivo);

    while (fgets(linha, TAM_LINHA, arquivo) && total < MAX_REGISTROS) {
        if (lerRestaurante(linha, &todos[total]))
            total++;
    }

    fclose(arquivo);

    // Parte 1: lê IDs e insere na lista encadeada
    ListaEncadeada lista;
    inicializarListaEnc(&lista);

    int buscaId;
    scanf("%d", &buscaId);

    while (buscaId != -1) {
        for (int i = 0; i < total; i++) {
            if (todos[i].id == buscaId) {
                inserirFimEnc(&lista, todos[i]);
                break;
            }
        }
        scanf("%d", &buscaId);
    }

    // Ordena por nome usando selection sort
    selectionSortEnc(&lista);

    // Imprime do primeiro ao último
    No *atual = lista.inicio;
    while (atual != NULL) {
        formatarRestaurante(&atual->dado);
        atual = atual->proximo;
    }

    // Libera memória
    No *temp;
    atual = lista.inicio;
    while (atual != NULL) {
        temp = atual;
        atual = atual->proximo;
        free(temp);
    }

    return 0;
}