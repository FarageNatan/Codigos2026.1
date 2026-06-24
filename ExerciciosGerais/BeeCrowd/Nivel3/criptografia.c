#include <stdio.h>
#include <stdlib.h>

int tamPalavra(char* frase){
    int tam = 0;

    while(frase[tam] != '\0'){
        tam++;
    }

    return tam;
}

void swap(char* frase, int j, int k){
    char tmp = frase[j];
    frase[j] = frase[k];
    frase[k] = tmp;
}

int main(){

    int casos = 0;
    scanf("%d", &casos);

    for(int i = 0; i < casos; i++){

        char* frase = (char*)malloc(1024 * sizeof(char));
        char* fraseP1 = (char*)malloc(1024 * sizeof(char));

        scanf(" %[^\n]", frase);

        // Primeira passada
        for(int j = 0; frase[j] != '\0'; j++){

            if((frase[j] >= 'A' && frase[j] <= 'Z') ||
               (frase[j] >= 'a' && frase[j] <= 'z')){

                fraseP1[j] = frase[j] + 3;
            }
            else{
                fraseP1[j] = frase[j];
            }
        }

        fraseP1[tamPalavra(frase)] = '\0';

        // Segunda passada
        int j = 0;
        int k = tamPalavra(fraseP1) - 1;

        while(j <= k){
            swap(fraseP1, j, k);
            j++;
            k--;
        }

        // Terceira passada
        for(int meio = tamPalavra(fraseP1) / 2;
            meio < tamPalavra(fraseP1);
            meio++){

            fraseP1[meio] = fraseP1[meio] - 1;
        }

        printf("%s\n", fraseP1);

        free(frase);
        free(fraseP1);
    }

    return 0;
}