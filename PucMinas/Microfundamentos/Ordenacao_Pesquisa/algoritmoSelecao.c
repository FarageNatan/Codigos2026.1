#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

void swap(int* vet, int i, int j){
	int temp = vet[i];
	vet[i] = vet[j];
	vet[j] = temp;
}

/*void imprimeVetor(char* vet[], int tamVet){
    for(int i = 0; i < tamVet; i++){   
	    printf("%s\n", vet[i]);
    }
}*/

//Versao Original
/*void ordenacaoSelecao(int* vet, int tam){
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
}*/

//Versao Decrescente
/*void selecaoDecrescente(int* vet, int tam){
	for(int i = 0; i < (tam - 1); i++){
		int maior = i;
		for(int j = (i + 1); j < tam; j++){
			if(vet[j] > vet[maior]){
				maior = j;
			}
		}
		swap(vet, maior, i);
        printf("Passagem: %d\n", i);
        imprimeVetor(vet, tam);
	}
}*/

void preencheVetor(int* vet, int tamVet){
    printf("Preencher Vetor: \n");
	for(int i = 0; i < tamVet; i++){
		scanf("%d", &vet[i]);
	}
}

bool compararStrings(char* p1, char* p2){
	bool resultado = true, terminou = true;
	int i = 0;
	while(p1[i] != '\0' && p2[i] != '\0' && terminou){
		if(p1[i] < p2[i]){
			resultado = false; //a string p1 eh menor
			terminou = false;
		}else if(p1[i] > p2[i]){
			terminou = false; //a string p2 eh maior
		}else{
			i++;
		}
	}

	//Se uma palavra termina primeiro, ela vem antes. (Ana, Anabele)
	if (terminou == false) {
        if (p1[i] == '\0' && p2[i] != '\0') { //A string p1 terminou e a p2 ainda tem letras o resultado vai ser que a string p1 vem antes.
            resultado = false;
        }
        else if (p1[i] != '\0' && p2[i] == '\0') { //A string p1 nao terminou e a p2 terminou o resultado vai ser que a string p1 vem depois.
            resultado = true;
        }
    }

	return resultado;
}

void ordenarAlfabetico(char* vetor[], int tam) {

    for (int i = 0; i < tam - 1; i++) {

        int menor = i;

        for (int j = i + 1; j < tam; j++) {

            if (compararStrings(vetor[j], vetor[menor]) == false) {
                menor = j;
            }
        }

        if (menor != i) {
            char* temp = vetor[i];
            vetor[i] = vetor[menor];
            vetor[menor] = temp;
        }
    }
}

int main(){
	int tamVet = 0;
    printf("Tamanho vetor: \n");
    scanf("%d", &tamVet);
    getchar(); 

    
    char vetorChar[tamVet][100]; 

    for (int i = 0; i < tamVet; i++) {
        scanf(" %[^\n]", vetorChar[i]);
    }

    
    char* ponteiros[tamVet];
    for (int i = 0; i < tamVet; i++) {
        ponteiros[i] = vetorChar[i];
    }

    ordenarAlfabetico(ponteiros, tamVet);

    printf("Vetor Ordenado:\n");
    for (int j = 0; j < tamVet; j++) {
        printf("%s\n", ponteiros[j]);
    }

    return 0;

}