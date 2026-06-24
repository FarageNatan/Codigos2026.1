#include <stdio.h>
 
int main() {
 
    int n1, n2;
    scanf("%d", &n1);
    scanf("%d", &n2);
    
    int soma = 0;

    int inicio = n1 < n2 ? n1 : n2;
    int fim    = n1 > n2 ? n1 : n2;

    for(int i = inicio; i <= fim; i++){
        if(i % 13 != 0){
            soma += i;
        }
    }
    
    printf("%d\n", soma);
 
    return 0;
}