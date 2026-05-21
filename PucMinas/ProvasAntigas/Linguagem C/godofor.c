#include <stdio.h>
#include <stdlib.h>

typedef struct Deus{
	char* nome;
	int poder;
	int matou;
	int morreu;
}Deus;


Deus* novoDeus(char* nome, int pod, int mat, int mor){
	struct Deus* novo = (Deus*)malloc(sizeof(Deus));
	novo->nome = (char*)malloc(100 * sizeof(char));
	novo->poder = pod;
	novo->matou = mat;
	novo->morreu = mor;
	return novo;
}

Deus* novoD(){
	struct Deus* novo = (Deus*)malloc(sizeof(Deus));
	novo->nome = (char*)malloc(100 * sizeof(char));
	novo->poder = 0;
	novo->matou = 0;
	novo->morreu = 0;
	return novo;
}


int comparaNum(int a, int b){
	if(a > b){
		return 1;
	}else if(a < b){
		return -1;
	}
	return 0;
}//fim comparaNum

int comparaNome(char* a, char* b){
	int i = 0;
	while(a[i] != '\0' && b[i] != '\0'){
		if(a[i] == '\0' || b[i] == '\0'){
			return (a[i] - b[i]);
		}
		i++;
	}	
	return (a[i] - b[i]);
}//fim comparaNome


int comparaDeus(Deus* a, Deus* b){
	int cmpPoder = comparaNum(a->poder, b->poder);
	if(cmpPoder != 0) return cmpPoder;
	
	int cmpMatou = comparaNum(a->matou, b->matou);
	if(cmpMatou != 0) return cmpMatou;

	int cmpMorreu = comparaNum(a->morreu, b->morreu);
	if(cmpMorreu != 0) return cmpMorreu;

	return comparaNome(a->nome, b->nome);
}//fim comparaDeus


void organizaDeuses(Deus** deuses, int candidatos){
	for(int i = 1; i < candidatos; i++){
		Deus* tmp = deuses[i];
		int j = i - 1;
		while(j >= 0 && comparaDeus(deuses[j], tmp) > 0){
			deuses[j + 1] = deuses[j];
			j--;
		}
		deuses[j + 1] = tmp;
	}
}//fim organiza



int main(){
	int candidatos;
	scanf("%d", &candidatos);

	int i = 0;
	while(i < candidatos){
		Deus** deuses = malloc(candidatos * sizeof(Deus));

		for(int d = 0; d < candidatos; d++){
			deuses[d] = novoD();
		}//fim iniciar

		for(int i = 0; i < candidatos; i++){
			scanf(" %s", deuses[i]->nome);
			scanf("%d", &deuses[i]->poder);
			scanf("%d", &deuses[i]->matou);
			scanf("%d", &deuses[i]->morreu);
		}//fim preenche deus
		 
		organizaDeuses(deuses, candidatos);

		for(int p = 0; p < candidatos; p++){
			printf("%s\n", deuses[p]->nome);
		}	
		i++;
	}//fim candidatos
	 

	
}//fim main
