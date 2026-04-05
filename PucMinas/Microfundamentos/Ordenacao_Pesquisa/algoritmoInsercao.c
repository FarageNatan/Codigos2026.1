#include <stdio.h>
#include <stdlib.h>

void insercao(int array[], int n){
	for(int i = 1; i < n; i++){
		int tmp = array[i];
		int j = i - 1;	
		while(j >= 0 && array[j] > tmp){
			array[j + 1] = array[j];
			j--;
		}//while
		array[j + 1] = tmp;
	}//for
}

int pesquisa(int array[], int tmp, int fim) {
    int esq = 0;
    int dir = fim;
    
    while (esq <= dir) {
        int meio = esq + (dir - esq) / 2;
        
        if (array[meio] < tmp) {
            esq = meio + 1;
        } else {
            dir = meio - 1;
        }
    }
    return esq;
}


void insercaoBinaria(int array[], int n){
	for(int i = 1; i < n; ++i){
		int tmp = array[i];
		int pos = pesquisa(array, tmp, i - 1);
		int j = i - 1;	
		while(j >= pos){
			array[j + 1] = array[j];
			j--;
		}//while
		array[pos] = tmp;
	}//for
}

int main(){
	int tam;
	scanf("%d", &tam);
	int* array = (int*)malloc(tam * sizeof(int));

	//Preenche
	for(int i = 0; i < tam; i++){
		scanf("%d", &array[i]);
	}

	//Desordenado
	for(int i = 0; i < tam; i++){
		printf("%d ", array[i]);
	}
    printf("\n");
	
	insercaoBinaria(array, tam);

	//Ordenado
	for(int i = 0; i < tam; i++){
		printf("%d ", array[i]);
	}
    printf("\n");

    free(array);
	return 0;
}