#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define TAM_LINHA 1024
#define MAX_REGISTROS 2000

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
    char tipos[20][50];
    int qtdTipos;
    int faixaPreco;
    Hora abertura;
    Hora fechamento;
    Data dataAbertura;
    bool aberto;
} Restaurante;

typedef struct No {
    Restaurante restaurante;
    struct No *esq;
    struct No *dir;
} No;

typedef struct {
    No *raiz;
    int comparacoes;
} ArvoreBinaria;

// --- Funções auxiliares (sem string.h) ---

int parseInt(char *s) {
    int resp = 0, inicio = 0;
    bool negativo = false;
    if (s == NULL || s[0] == '\0') return 0;
    if (s[0] == '-') { negativo = true; inicio = 1; }
    for (int i = inicio; s[i] != '\0'; i++) {
        if (s[i] >= '0' && s[i] <= '9')
            resp = resp * 10 + (s[i] - '0');
    }
    return negativo ? -resp : resp;
}

double parseDouble(char *s) {
    double resp = 0, decimal = 0.1;
    bool ponto = false;
    for (int i = 0; s[i] != '\0'; i++) {
        if (s[i] == '.') {
            ponto = true;
        } else if (s[i] >= '0' && s[i] <= '9') {
            if (!ponto) resp = resp * 10 + (s[i] - '0');
            else { resp += (s[i] - '0') * decimal; decimal /= 10; }
        }
    }
    return resp;
}

int compararString(char *a, char *b) {
    int i = 0;
    while (a[i] != '\0' && b[i] != '\0') {
        if (a[i] < b[i]) return -1;
        if (a[i] > b[i]) return  1;
        i++;
    }
    if (a[i] == '\0' && b[i] == '\0') return  0;
    if (a[i] == '\0')                 return -1;
    return 1;
}

bool igual(char *a, char *b) {
    return compararString(a, b) == 0;
}

void doisDigitos(int n, char *buf) {
    if (n < 10) sprintf(buf, "0%d", n);
    else        sprintf(buf, "%d", n);
}

void quatroDigitos(int n, char *buf) {
    if      (n < 10)   sprintf(buf, "000%d", n);
    else if (n < 100)  sprintf(buf, "00%d",  n);
    else if (n < 1000) sprintf(buf, "0%d",   n);
    else               sprintf(buf, "%d",    n);
}

void umaCasa(double valor, char *buf) {
    int inteiro  = (int) valor;
    int decimal  = (int)((valor - inteiro) * 10 + 0.5);
    sprintf(buf, "%d.%d", inteiro, decimal);
}

// --- Parsing ---

int parseCampos(char *linha, char campos[][200], int maxCampos) {
    int idx = 0, buf = 0, aspas = 0, i = 0;
    while (linha[i] != '\0' && idx < maxCampos) {
        if      (linha[i] == '"')              { aspas = !aspas; }
        else if (linha[i] == ',' && !aspas)    { campos[idx++][buf] = '\0'; buf = 0; }
        else                                   { campos[idx][buf++] = linha[i]; }
        i++;
    }
    campos[idx][buf] = '\0';
    int j = 0;
    while (campos[idx][j] != '\0' && campos[idx][j] != '\r' && campos[idx][j] != '\n') j++;
    campos[idx][j] = '\0';
    return ++idx;
}

Hora parseHora(char *s) {
    Hora h = {0, 0};
    int i = 0;
    while (s[i] != ':') { h.hora   = h.hora   * 10 + (s[i] - '0'); i++; } i++;
    while (s[i] != '\0') { h.minuto = h.minuto * 10 + (s[i] - '0'); i++; }
    return h;
}

Data parseData(char *s) {
    Data d = {0, 0, 0};
    int i = 0;
    while (s[i] != '-') { d.ano = d.ano * 10 + (s[i] - '0'); i++; } i++;
    while (s[i] != '-') { d.mes = d.mes * 10 + (s[i] - '0'); i++; } i++;
    while (s[i] != '\0') { d.dia = d.dia * 10 + (s[i] - '0'); i++; }
    return d;
}

Restaurante parseRestaurante(char *linha) {
    Restaurante r = {0};
    char campos[12][200];
    parseCampos(linha, campos, 12);

    r.id         = parseInt(campos[0]);
    // copia nome e cidade manualmente
    int i = 0;
    while (campos[1][i] != '\0') { r.nome[i]   = campos[1][i]; i++; } r.nome[i]   = '\0';
    i = 0;
    while (campos[2][i] != '\0') { r.cidade[i] = campos[2][i]; i++; } r.cidade[i] = '\0';
    r.capacidade = parseInt(campos[3]);
    r.avaliacao  = parseDouble(campos[4]);

    // tipos separados por ';'
    r.qtdTipos = 0;
    int pos = 0;
    i = 0;
    while (campos[5][i] != '\0') {
        if (campos[5][i] == ';') {
            r.tipos[r.qtdTipos][pos] = '\0';
            r.qtdTipos++; pos = 0;
        } else { r.tipos[r.qtdTipos][pos++] = campos[5][i]; }
        i++;
    }
    r.tipos[r.qtdTipos][pos] = '\0';
    r.qtdTipos++;

    r.faixaPreco = 0;
    i = 0;
    while (campos[6][i] != '\0') { if (campos[6][i] == '$') r.faixaPreco++; i++; }

    // horario HH:MM-HH:MM
    char h1[10] = {0}, h2[10] = {0};
    i = 0; int k = 0;
    while (campos[7][i] != '-') { h1[k++] = campos[7][i++]; } h1[k] = '\0'; i++;
    k = 0;
    while (campos[7][i] != '\0') { h2[k++] = campos[7][i++]; } h2[k] = '\0';
    r.abertura   = parseHora(h1);
    r.fechamento = parseHora(h2);

    r.dataAbertura = parseData(campos[8]);
    r.aberto = igual(campos[9], "true");
    return r;
}

void formatarRestaurante(Restaurante *r) {
    char tiposStr[500], faixa[10], av[10];
    char dAb[6], dMes[6], dAno[6];
    char hAb[6], hAbMin[6], hFe[6], hFeMin[6];
    int offset = 0;

    offset += sprintf(tiposStr + offset, "[");
    for (int i = 0; i < r->qtdTipos; i++) {
        if (i > 0) offset += sprintf(tiposStr + offset, ",");
        offset += sprintf(tiposStr + offset, "%s", r->tipos[i]);
    }
    sprintf(tiposStr + offset, "]");

    for (int i = 0; i < r->faixaPreco; i++) faixa[i] = '$';
    faixa[r->faixaPreco] = '\0';

    umaCasa(r->avaliacao, av);
    doisDigitos(r->dataAbertura.dia,  dAb);
    doisDigitos(r->dataAbertura.mes,  dMes);
    quatroDigitos(r->dataAbertura.ano, dAno);
    doisDigitos(r->abertura.hora,    hAb);
    doisDigitos(r->abertura.minuto,  hAbMin);
    doisDigitos(r->fechamento.hora,  hFe);
    doisDigitos(r->fechamento.minuto,hFeMin);

    printf("[%d ## %s ## %s ## %d ## %s ## %s ## %s ## %s:%s-%s:%s ## %s/%s/%s ## %s]\n",
        r->id, r->nome, r->cidade, r->capacidade, av,
        tiposStr, faixa,
        hAb, hAbMin, hFe, hFeMin,
        dAb, dMes, dAno,
        r->aberto ? "true" : "false");
}

// --- Árvore Binária ---

void iniciarArvore(ArvoreBinaria *a) {
    a->raiz = NULL;
    a->comparacoes = 0;
}

No *criarNo(Restaurante r) {
    No *novo = (No *)malloc(sizeof(No));
    novo->restaurante = r;
    novo->esq = NULL;
    novo->dir = NULL;
    return novo;
}

No *inserir(No *i, Restaurante r) {
    if (i == NULL) return criarNo(r);
    int cmp = compararString(r.nome, i->restaurante.nome);
    if      (cmp < 0) i->esq = inserir(i->esq, r);
    else if (cmp > 0) i->dir = inserir(i->dir, r);
    // cmp == 0: duplicata, não insere
    return i;
}

bool pesquisar(No *i, char *nome, ArvoreBinaria *a) {
    if (i == NULL) return false;
    a->comparacoes++;
    int cmp = compararString(nome, i->restaurante.nome);
    if (cmp == 0) return true;
    if (cmp < 0) { printf("esq "); return pesquisar(i->esq, nome, a); }
    else         { printf("dir "); return pesquisar(i->dir, nome, a); }
}

void caminharCentral(No *i) {
    if (i == NULL) return;
    caminharCentral(i->esq);
    formatarRestaurante(&i->restaurante);
    caminharCentral(i->dir);
}

void liberarArvore(No *i) {
    if (i == NULL) return;
    liberarArvore(i->esq);
    liberarArvore(i->dir);
    free(i);
}

void criarLog(char *matricula, int comparacoes, double tempo) {
    char nomeArquivo[100];
    sprintf(nomeArquivo, "%s_arvore_binaria.txt", matricula);
    FILE *f = fopen(nomeArquivo, "w");
    if (f) {
        char tempoStr[20];
        sprintf(tempoStr, "%.2f", tempo);
        fprintf(f, "%s\t%d\t%s\n", matricula, comparacoes, tempoStr);
        fclose(f);
    }
}

// --- Coleção ---

typedef struct {
    Restaurante restaurantes[MAX_REGISTROS];
    int tamanho;
} ColecaoRestaurantes;

void lerCsv(ColecaoRestaurantes *c) {
    FILE *arq = fopen("/tmp/restaurantes.csv", "r");
    if (!arq) { printf("Erro ao abrir arquivo\n"); return; }
    char linha[TAM_LINHA];
    fgets(linha, TAM_LINHA, arq); // pula cabeçalho
    c->tamanho = 0;
    while (fgets(linha, TAM_LINHA, arq) && c->tamanho < MAX_REGISTROS)
        c->restaurantes[c->tamanho++] = parseRestaurante(linha);
    fclose(arq);
}

Restaurante *buscar(ColecaoRestaurantes *c, int id) {
    for (int i = 0; i < c->tamanho; i++)
        if (c->restaurantes[i].id == id)
            return &c->restaurantes[i];
    return NULL;
}

// --- Main ---

int main() {
    ColecaoRestaurantes c;
    lerCsv(&c);

    ArvoreBinaria arvore;
    iniciarArvore(&arvore);

    char linha[TAM_LINHA];

    fgets(linha, TAM_LINHA, stdin);
    while (linha[0] != '\0') {
        int id = parseInt(linha);
        if (id == -1) break;
        Restaurante *r = buscar(&c, id);
        if (r != NULL)
            arvore.raiz = inserir(arvore.raiz, *r);
        fgets(linha, TAM_LINHA, stdin);
    }

    fgets(linha, TAM_LINHA, stdin);
    while (linha[0] != '\0') {
        int j = 0;
        while (linha[j] != '\0' && linha[j] != '\r' && linha[j] != '\n') j++;
        linha[j] = '\0';

        if (igual(linha, "FIM")) break;

        printf("raiz ");
        bool resp = pesquisar(arvore.raiz, linha, &arvore);
        printf("%s\n", resp ? "SIM" : "NAO");

        fgets(linha, TAM_LINHA, stdin);
    }

    caminharCentral(arvore.raiz);

    liberarArvore(arvore.raiz);
    return 0;
}