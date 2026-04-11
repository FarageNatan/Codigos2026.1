#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int tamanho(char* p){
    int tam = 0;
    while(p[tam] != '\0'){
        tam++;
    }
    return tam;
}

void separaPalavras(char* linha, char* p1, char* p2){
    int i = 0, j = 0;

    while(linha[i] != ' ' && linha[i] != '\0'){
        p1[j++] = linha[i++];
    }
    p1[j] = '\0';

    while(linha[i] == ' '){
        i++;
    }

    j = 0;
    while(linha[i] != '\0'){
        p2[j++] = linha[i++];
    }
    p2[j] = '\0';
}

bool ehAnagrama(char* p1, char* p2){
    int t1 = tamanho(p1);
    int t2 = tamanho(p2);

    bool resp = true;

    if(t1 != t2){
        resp = false;
    }else{
        int freq[256] = {0};

        int i = 0;
        while(p1[i] != '\0'){
            char c = p1[i];

            if(c >= 'A' && c <= 'Z'){
                c = c + 32;
            }

            freq[(int)c]++;
            i++;
        }

        i = 0;
        while(p2[i] != '\0'){
            char c = p2[i];

            if(c >= 'A' && c <= 'Z'){
                c = c + 32;
            }

            freq[(int)c]--;
            i++;
        }

        for(i = 0; i < 256; i++){
            if(freq[i] != 0){
                resp = false;
            }
        }
    }
    return resp;
}

int main(){
    char linha[100];
    char* p1;
    char* p2;
    
    p1 = (char*)malloc(100*sizeof(char));
    p2 = (char*)malloc(100*sizeof(char));

    while(fgets(linha, 100, stdin) != NULL){

        int tam = tamanho(linha);
        if(tam > 0 && linha[tam - 1] == '\n'){
            linha[tam - 1] = '\0';
        }

        separaPalavras(linha, p1, p2);
        
        bool resp = ehAnagrama(p1, p2);

        if(resp){
            printf("SIM\n");
        }else{
            printf("NAO\n");
        }
    }

    free(p1);
    free(p2);
    return 0;
}