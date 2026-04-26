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

// --- Main ---

int main() {
    //FILE *arquivo = fopen("../dataset/restaurantes.csv", "r");
    FILE *arquivo = fopen("/tmp/restaurantes.csv", "r");
    if (!arquivo) {
        printf("Erro ao abrir o arquivo\n");
        return 1;
    }

    Restaurante lista[MAX_REGISTROS];
    int total = 0;
    char linha[TAM_LINHA];

    fgets(linha, TAM_LINHA, arquivo); // pula cabeçalho

    while (fgets(linha, TAM_LINHA, arquivo) && total < MAX_REGISTROS) {
        if (lerRestaurante(linha, &lista[total]))
            total++;
    }

    fclose(arquivo);

    int buscaId;
    scanf("%d", &buscaId);

    while (buscaId != -1) {
        for (int i = 0; i < total; i++) {
            if (lista[i].id == buscaId) {
                formatarRestaurante(&lista[i]);
                break;
            }
        }
        scanf("%d", &buscaId);
    }

    return 0;
}