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
	
	insercao(array, tam);

	//Ordenado
	for(int i = 0; i < tam; i++){
		printf("%d ", array[i]);
	}
    printf("\n");

    free(array);
	return 0;
}