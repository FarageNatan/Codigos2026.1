#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

char* tratafgets(char* palavra, int tam){
    if (tam > 0 && palavra[tam - 1] == '\n') {
        palavra[tam - 1] = '\0';
        tam--;
    }
    return palavra;
}

int tamanhoPalavra(char* p1){
    int tam = 0;
    while(p1[tam] != '\0'){
        tam++;
    }
    return tam;
}

bool confereAnagrama(char* p1, char* p2){
    int tam1 = tamanhoPalavra(p1);
    int tam2 = tamanhoPalavra(p2);
    bool ehAnagrama = true;

    if(tam1 != tam2){
        ehAnagrama = false;
    }

    int freq[256] = {0};

    for(int i = 0; i < tam1; i++){
        char c = p1[i];
        if(c >= 'A' && c <= 'Z'){
            c = c + 32; 
        }
        freq[(int)c]++;
    }

    for(int i = 0; i < tam2; i++){
        char c = p2[i];
        if(c >= 'A' && c <= 'Z'){
            c = c + 32;
        }
        freq[(int)c]--;
    }

    //percorre linearmente o vetor de frenquencia, se a frequencia for diferente de 0, a palavra nao eh um anagrama porque ou tem mais de uma mesma letra em apenas uma palavra ou tem uma letra que esta presente em apenas uma palavra.
    for(int i = 0; i < 256; i++){
        if(freq[i] != 0){
            ehAnagrama = false;
        }
    }

    return ehAnagrama;
}

//Por causa da entrada do verde temos que tratar tambem o hifen fazendo essa funcao de separar, que copia a primeira parte da linha, pula os espaços e hífen e copia a segunda parte da linha para fazer a comparação
void separar(char* linha, char* p1, char* p2){
    int i = 0, j = 0;

    
    while(linha[i] != '-' && linha[i] != '\0'){
        p1[j++] = linha[i++];
    }
    p1[j] = '\0';

    j--;
    while(j >= 0 && p1[j] == ' '){
        p1[j] = '\0';
        j--;
    }

    if(linha[i] == '-') i++;
    while(linha[i] == ' ') i++;

    j = 0;
    while(linha[i] != '\0'){
        p2[j++] = linha[i++];
    }
    p2[j] = '\0';
}

int main(){
    char* linha = malloc(1000 * sizeof(char));
    char p1[500], p2[500];

    fgets(linha, 1000, stdin);
    int tam = tamanhoPalavra(linha);
    tratafgets(linha, tam);

    separar(linha, p1, p2);

    while(!(p1[0] == 'F' && p1[1] == 'I' && p1[2] == 'M' && p1[3] == '\0')){

        if(confereAnagrama(p1, p2)){
            printf("SIM\n");
        } else {
            printf("NÃO\n");
        }

        fgets(linha, 1000, stdin);
        tam = tamanhoPalavra(linha);
        tratafgets(linha, tam);

        separar(linha, p1, p2);
    }

    free(linha);
    return 0;
}