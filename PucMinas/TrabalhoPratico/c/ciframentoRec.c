#include <stdio.h>

void cifraRecursiva(char* str, int i){
    if(str[i] != '\0'){
        char c = str[i];

        if(c >= 0 && c <= 127){
            c = (c + 3) % 128;
        }

        printf("%c", c);

        cifraRecursiva(str, i + 1);
    }
}

int ehFim(char* str){
    int resp = 0;

    if(str[0] == 'F' && str[1] == 'I' && str[2] == 'M' && str[3] == '\0'){
        resp = 1;
    }

    return resp;
}

int main(){
    char linha[1000];
    int tam;

    fgets(linha, 1000, stdin);

    tam = 0;
    while(linha[tam] != '\0') tam++;
    if(tam > 0 && linha[tam-1] == '\n'){
        linha[tam-1] = '\0';
    }

    while(!ehFim(linha)){

        cifraRecursiva(linha, 0);
        printf("\n");

        fgets(linha, 1000, stdin);

        tam = 0;
        while(linha[tam] != '\0') tam++;
        if(tam > 0 && linha[tam-1] == '\n'){
            linha[tam-1] = '\0';
        }
    }

    return 0;
}