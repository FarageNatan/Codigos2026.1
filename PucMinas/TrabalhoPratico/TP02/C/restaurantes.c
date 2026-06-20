#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#define TAM_LINHA 1024
#define MAX_REGISTROS 1000
#define TAM_TABELA 31
#define TAM_RESERVA 19
#define TAM_TOTAL (TAM_TABELA + TAM_RESERVA)

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

    campos[idx_campos][idx_buffer] = '\0';
    int j = 0;
    while (campos[idx_campos][j] != '\0' && campos[idx_campos][j] != '\r' && campos[idx_campos][j] != '\n') j++;
    campos[idx_campos][j] = '\0';
    idx_campos++;

    return idx_campos;
}

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

typedef struct NoHash {
    Restaurante dado;
    struct NoHash *proximo;
} NoHash;

typedef struct {
    NoHash *tabela[TAM_TABELA];
} TabelaHashIndireta;

void inicializarHash(TabelaHashIndireta *h) {
    for (int i = 0; i < TAM_TABELA; i++) {
        h->tabela[i] = NULL;
    }
}

int calcularHash(char *nome) {
    int soma = 0;
    for (int i = 0; nome[i] != '\0'; i++) {
        soma += (int)nome[i];
    }
    return soma % TAM_TABELA;
}

void inserirHash(TabelaHashIndireta *h, Restaurante r) {
    int pos = calcularHash(r.nome);

    // Evita inserção de duplicatas na mesma lista
    NoHash *atual = h->tabela[pos];
    while (atual != NULL) {
        if (strcmp(atual->dado.nome, r.nome) == 0) {
            return; 
        }
        atual = atual->proximo;
    }

    // Inserção no fim da lista encadeada daquela posição
    NoHash *novo = (NoHash *)malloc(sizeof(NoHash));
    novo->dado = r;
    novo->proximo = NULL;

    if (h->tabela[pos] == NULL) {
        h->tabela[pos] = novo;
    } else {
        NoHash *p = h->tabela[pos];
        while (p->proximo != NULL) {
            p = p->proximo;
        }
        p->proximo = novo;
    }
}

int pesquisarHash(TabelaHashIndireta *h, char *nome) {
    int pos = calcularHash(nome);
    NoHash *atual = h->tabela[pos];

    while (atual != NULL) {
        if (strcmp(atual->dado.nome, nome) == 0) {
            return pos;
        }
        atual = atual->proximo;
    }

    return -1;
}

void liberarHash(TabelaHashIndireta *h) {
    for (int i = 0; i < TAM_TABELA; i++) {
        NoHash *atual = h->tabela[i];
        while (atual != NULL) {
            NoHash *aux = atual->proximo;
            free(atual);
            atual = aux;
        }
        h->tabela[i] = NULL;
    }
}

typedef struct NoLista {
    Restaurante dado;
    struct NoLista *proximo;
} NoLista;

typedef struct NoArvore {
    char chave;
    NoLista *primeiro;
    struct NoArvore *esq;
    struct NoArvore *dir;
} NoArvore;

NoArvore* criarNoArvore(char chave) {
    NoArvore *novo = (NoArvore*)malloc(sizeof(NoArvore));
    novo->chave = chave;
    novo->primeiro = NULL;
    novo->esq = NULL;
    novo->dir = NULL;
    return novo;
}

void inserirListaOrdenada(NoLista **topo, Restaurante r) {
    NoLista *novo = (NoLista*)malloc(sizeof(NoLista));
    novo->dado = r;
    novo->proximo = NULL;

    if (*topo == NULL || strcmp(r.nome, (*topo)->dado.nome) < 0) {
        novo->proximo = *topo;
        *topo = novo;
    } else {
        NoLista *atual = *topo;
        while (atual->proximo != NULL && strcmp(atual->proximo->dado.nome, r.nome) < 0) {
            atual = atual->proximo;
        }
        novo->proximo = atual->proximo;
        atual->proximo = novo;
    }
}

NoArvore* inserirArvore(NoArvore *raiz, Restaurante r) {
    char letra = r.nome[0];
    if (raiz == NULL) {
        NoArvore *novo = criarNoArvore(letra);
        inserirListaOrdenada(&(novo->primeiro), r);
        return novo;
    }

    if (letra < raiz->chave) {
        raiz->esq = inserirArvore(raiz->esq, r);
    } else if (letra > raiz->chave) {
        raiz->dir = inserirArvore(raiz->dir, r);
    } else {
        inserirListaOrdenada(&(raiz->primeiro), r);
    }
    return raiz;
}

void pesquisarArvoreLista(NoArvore *raiz, char *nome) {
    char letra = nome[0];
    NoArvore *atual = raiz;
    int primeiroPonteiro = 1;

    while (atual != NULL) {
        if (!primeiroPonteiro) printf(" ");
        if (atual == raiz && primeiroPonteiro) printf("RAIZ");

        if (letra == atual->chave) {
            NoLista *nodoLista = atual->primeiro;
            while (nodoLista != NULL) {
                int cmp = strcmp(nome, nodoLista->dado.nome);
                if (cmp == 0) {
                    printf(" SIM\n");
                    formatarRestaurante(&(nodoLista->dado));
                    return;
                }
                printf(" %s", nodoLista->dado.nome);
                nodoLista = nodoLista->proximo;
            }
            break; 
        } else if (letra < atual->chave) {
            atual = atual->esq;
            if (atual != NULL) printf(" ESQ");
        } else {
            atual = atual->dir;
            if (atual != NULL) printf(" DIR");
        }
        primeiroPonteiro = 0;
    }
    printf(" NAO\n");
}

void liberarArvoreLista(NoArvore *raiz) {
    if (raiz == NULL) return;
    liberarArvoreLista(raiz->esq);
    liberarArvoreLista(raiz->dir);
    
    NoLista *atual = raiz->primeiro;
    while (atual != NULL) {
        NoLista *aux = atual->proximo;
        free(atual);
        atual = aux;
    }
    free(raiz);
}

// --- Estruturas da Árvore Trie com Lista Flexível ---

struct NoTrie;

// Célula da lista encadeada (lista flexível) que aponta para os nós filhos
typedef struct CelulaTrie {
    char elemento;
    struct NoTrie *noFilho;
    struct CelulaTrie *proximo;
} CelulaTrie;

// Nó da Árvore Trie
typedef struct NoTrie {
    CelulaTrie *primeiro; // Sentinela da lista flexível de filhos
    CelulaTrie *ultimo;
    bool ehFim;           // True se uma palavra termina aqui
    Restaurante dado;     // Armazena o registro do restaurante se ehFim for true
} NoTrie;

NoTrie* criarNoTrie() {
    NoTrie *novo = (NoTrie*)malloc(sizeof(NoTrie));
    novo->ehFim = false;
    
    // Inicializa a lista flexível com um nó sentinela
    novo->primeiro = (CelulaTrie*)malloc(sizeof(CelulaTrie));
    novo->primeiro->proximo = NULL;
    novo->ultimo = novo->primeiro;
    
    return novo;
}

CelulaTrie* pesquisarFilho(NoTrie *no, char c) {
    CelulaTrie *atual = no->primeiro->proximo;
    while (atual != NULL) {
        if (atual->elemento == c) {
            return atual;
        }
        atual = atual->proximo;
    }
    return NULL;
}

void inserirFilho(NoTrie *no, char c, NoTrie *filho) {
    CelulaTrie *novo = (CelulaTrie*)malloc(sizeof(CelulaTrie));
    novo->elemento = c;
    novo->noFilho = filho;
    novo->proximo = NULL;
    
    no->ultimo->proximo = novo;
    no->ultimo = novo;
}

void inserirTrie(NoTrie *raiz, Restaurante r) {
    NoTrie *atual = raiz;
    char *nome = r.nome;
    
    for (int i = 0; nome[i] != '\0'; i++) {
        char c = nome[i];
        CelulaTrie *celula = pesquisarFilho(atual, c);
        
        if (celula == NULL) {
            NoTrie *novoFilho = criarNoTrie();
            inserirFilho(atual, c, novoFilho);
            atual = novoFilho;
        } else {
            atual = celula->noFilho;
        }
    }
    atual->ehFim = true;
    atual->dado = r;
}

void pesquisarTrie(NoTrie *raiz, char *nome) {
    NoTrie *atual = raiz;
    
    for (int i = 0; nome[i] != '\0'; i++) {
        char c = nome[i];
        
        CelulaTrie *celula = pesquisarFilho(atual, c);
        if (celula == NULL) {
            printf(" NAO\n");
            return;
        }
        
        printf("%c ", c);
        atual = celula->noFilho;
    }
    
    if (atual->ehFim) {
        printf("SIM ");
        formatarRestaurante(&(atual->dado));
    } else {
        printf("NAO\n");
    }
}

void liberarTrie(NoTrie *no) {
    if (no == NULL) return;
    
    CelulaTrie *atual = no->primeiro->proximo;
    while (atual != NULL) {
        CelulaTrie *aux = atual->proximo;
        liberarTrie(atual->noFilho);
        free(atual);
        atual = aux;
    }
    free(no->primeiro); // Libera o nó sentinela
    free(no);
}

int main() {
    FILE *arquivo = fopen("/tmp/restaurantes.csv", "r");
    if (!arquivo) {
        printf("Erro ao abrir o arquivo\n");
        return 1;
    }

    Restaurante todos[MAX_REGISTROS];
    int total = 0;
    char linha[TAM_LINHA];

    fgets(linha, TAM_LINHA, arquivo);

    while (fgets(linha, TAM_LINHA, arquivo) && total < MAX_REGISTROS) {
        if (lerRestaurante(linha, &todos[total])) total++;
    }
    fclose(arquivo);

    NoTrie *raiz = criarNoTrie();
    int buscaId;
    
    if (scanf("%d", &buscaId) != 1) return 0;

    while (buscaId != -1) {
        for (int i = 0; i < total; i++) {
            if (todos[i].id == buscaId) {
                inserirTrie(raiz, todos[i]);
                break;
            }
        }
        if (scanf("%d", &buscaId) != 1) break;
    }

    char nomeBusca[100];
    if (scanf(" %[^\n]", nomeBusca) != 1) return 0;

    while (strcmp(nomeBusca, "FIM") != 0) {
        pesquisarTrie(raiz, nomeBusca);
        if (scanf(" %[^\n]", nomeBusca) != 1) break;
    }

    liberarTrie(raiz);
    return 0;
}