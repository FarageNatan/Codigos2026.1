#include <stdio.h>
#include <stdlib.h>

int main(){
    int casos = 0;
    scanf("%d", &casos);

    for(int n = 0; n < casos; n++){
        
        char* frase = (char*)malloc(2048 * sizeof(char));
        int cont = 0;
        int letras[26];

        for(int i = 0; i < 26; i++){
            letras[i] = 0;
        }

        scanf(" %[^\n]", frase);

        for(int f = 0; frase[f] != '\0'; f++){
            if(frase[f] >= 'a' && frase[f] <= 'z'){
                int pos = frase[f] - 'a';

                if(letras[pos] == 0){
                    letras[pos] = 1;
                    cont++;
                }
            }
        }

        if(cont == 26){
            printf("frase completa\n");
        }else if(cont >= 13){
            printf("frase quase completa\n");
        }else{
            printf("frase mal elaborada\n");
        }
    }
        
    return 0;
}