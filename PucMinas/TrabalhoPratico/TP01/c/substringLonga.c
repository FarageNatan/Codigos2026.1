#include <stdio.h>

int tamanho(char str[]){
    int i = 0;
    while(str[i] != '\0'){
        i++;
    }
    return i;
}

int maiorSubstring(char str[]){
    int n = tamanho(str);
    int max = 0;
    int i = 0;

    while(i < n){
        int freq[256];
        int j = 0;

        while(j < 256){
            freq[j] = 0;
            j++;
        }

        j = i;
        int atual = 0;
        int repetiu = 0;

        while(j < n && repetiu == 0){
            int c = (int)str[j];

            if(freq[c] == 1){
                repetiu = 1;
            } else {
                freq[c] = 1;
                atual++;
            }

            j++;
        }

        if(atual > max){
            max = atual;
        }

        i++;
    }

    return max;
}

int main(){
    char str[1000];

    int continuar = 1;

    while(continuar == 1){
        scanf("%s", str);
        if(str[0]=='F' && str[1]=='I' && str[2]=='M' && str[3]=='\0'){
            continuar = 0;
        } else {
            int resultado = maiorSubstring(str);
            printf("%d\n", resultado);
        }
    }

    return 0;
}