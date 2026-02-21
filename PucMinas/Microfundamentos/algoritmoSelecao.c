#include <stdio.h>
#include <stdlib.h>

void swap(int* vet, int i, int j){
	int temp = vet[i];
	vet[i] = vet[j];
	vet[j] = temp;
}

void imprimeVetor(int* vet, int tamVet){
    for(int i = 0; i < tamVet; i++){   
	    printf("%d\n", vet[i]);
    }
}

//Versao Original
void ordenacaoSelecao(int* vet, int tam){
	for(int i = 0; i < (tam - 1); i++){
		int menor = i;
		for(int j = (i + 1); j < tam; j++){
			if(vet[j] < vet[menor]){
				menor = j;
			}
		}
		swap(vet, menor, i);
        printf("Passagem: %d\n", i);
        imprimeVetor(vet, tam);
	}
}

void preencheVetor(int* vet, int tamVet){
    printf("Preencher Vetor: \n");
	for(int i = 0; i < tamVet; i++){
		scanf("%d", &vet[i]);
	}
}


int main(){
	
	int tamVet = 0;
    printf("Tamanho vetor: \n");
	scanf("%d", &tamVet);	
	int vetor[tamVet];
	preencheVetor(vetor, tamVet);
	ordenacaoSelecao(vetor, tamVet);
	//printf("Vetor Ordenado: \n");
	//imprimeVetor(vetor, tamVet);

	return 0;
}