#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct TabelaHashReserva
{
    char** tabela;
    int m;
    int r;
    int nr;
}TabelaHashReserva;

TabelaHashReserva* newHash(int M, int R){
    TabelaHashReserva* hash = (TabelaHashReserva*)malloc(sizeof(TabelaHashReserva));
    hash->tabela = (char**)malloc((M + R) * sizeof(char*)); //Quantidade de posicoes disponiveis (sem contar a reserva)

    for(int i = 0; i < M+R; i++) hash->tabela[i] = NULL;

    hash->m = M; //Tamanho total da tabela (posicoes + area de reserva)
    hash->r = R; //Tamanho da área de reserva
    hash->nr = 0; //Quantidade de elementos na reserva
    return hash;
}

int tamString(char* s){
    int tam = 0;
    while(s[tam] != '\0'){
        tam++;
    }
    return 0;
}

int hash(TabelaHashReserva* hash, char* chave){
    int soma = 0;
    int tam = tamString(chave);
    for(int i = 0; i < tam; i++){
        soma += chave[i];
    }
    int valor = soma % hash->m;
    return valor;
}

bool isPosicaoLivre(TabelaHashReserva* hash, int pos){
    bool resp;
    if(hash->tabela[pos] == NULL){
        resp = true;
    }else{
        resp = false;
    }
    return resp;
}






int main(){




    return 0;
}