#include <stdio.h>

int ehVogal(char c){
    int resp = 0;
    if(c=='a'||c=='A'||c=='e'||c=='E'||c=='i'||c=='I'||c=='o'||c=='O'||c=='u'||c=='U'){
        resp = 1;
    }
    return resp;
}

int ehLetra(char c){
    int resp = 0;
    if((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')){
        resp = 1;
    }
    return resp;
}

int confereVogal(char* str, int i){
    int resp = 1;

    if(str[i] != '\0'){
        if(!ehVogal(str[i])){
            resp = 0;
        } else {
            resp = confereVogal(str, i+1);
        }
    }

    return resp;
}

int confereConsoante(char* str, int i){
    int resp = 1;

    if(str[i] != '\0'){
        if(!ehLetra(str[i]) || ehVogal(str[i])){
            resp = 0;
        } else {
            resp = confereConsoante(str, i+1);
        }
    }

    return resp;
}

int confereInteiro(char* str, int i){
    int resp = 1;

    if(str[i] != '\0'){
        if(!(str[i] >= '0' && str[i] <= '9')){
            resp = 0;
        } else {
            resp = confereInteiro(str, i+1);
        }
    }

    return resp;
}

int confereReal(char* str, int i, int ponto){
    int resp = 1;

    if(str[i] != '\0'){
        if(str[i] == '.' || str[i] == ','){
            ponto++;
            if(ponto > 1){
                resp = 0;
            } else {
                resp = confereReal(str, i+1, ponto);
            }
        } else if(str[i] >= '0' && str[i] <= '9'){
            resp = confereReal(str, i+1, ponto);
        } else {
            resp = 0;
        }
    }

    return resp;
}

int ehFim(char* str){
    int resp = 0;
    if(str[0]=='F' && str[1]=='I' && str[2]=='M' && str[3]=='\0'){
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

        if(confereVogal(linha, 0)) printf("SIM ");
        else printf("NAO ");

        if(confereConsoante(linha, 0)) printf("SIM ");
        else printf("NAO ");

        if(confereInteiro(linha, 0)) printf("SIM ");
        else printf("NAO ");

        if(confereReal(linha, 0, 0)) printf("SIM\n");
        else printf("NAO\n");

        fgets(linha, 1000, stdin);

        tam = 0;
        while(linha[tam] != '\0') tam++;
        if(tam > 0 && linha[tam-1] == '\n'){
            linha[tam-1] = '\0';
        }
    }

    return 0;
}