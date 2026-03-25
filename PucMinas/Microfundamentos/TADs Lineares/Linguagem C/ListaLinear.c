#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    int* array;
    int n;    
}Lista;

void inicializarLista(Lista lista, int tamanho){
    lista.array = (int*)malloc(tamanho * sizeof(int));
}





int main(){



    return 0;
}