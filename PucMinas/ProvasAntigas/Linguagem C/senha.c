#include <stdio.h>
#include <stdlib.h>

int tamanhoFrase(char* frase){
	int tam = 0;
	while(frase[tam] != '\0'){
		tam++;
	}
	return tam;
}

int main(){
	int quantidade = 0;
	scanf("%d", &quantidade);

	int i = 0;
	while(i < quantidade){
		char frase[100];
		scanf(" %[^\n]", frase);
		int tam = tamanhoFrase(frase);
		int posEscrita = 0;

		for(int j = 0; j < tam; j++){
			if(frase[j] != ' '){
				if(frase[j] == 'G' || frase[j] == 'Q' || frase[j] == 'a' || frase[j] == 'k' || frase[j] == 'u'){
					frase[posEscrita] = '0';
				}else if(frase[j] == 'I' || frase[j] == 'S' || frase[j] == 'b' || frase[j] == 'l' || frase[j] == 'v'){
					frase[posEscrita] = '1';
				}else if(frase[j] == 'E' || frase[j] == 'O' || frase[j] == 'Y' || frase[j] == 'c' || frase[j] == 'm' || frase[j] == 'w'){
					frase[posEscrita] = '2';
				}else if(frase[j] == 'F' || frase[j] == 'P' || frase[j] == 'Z' || frase[j] == 'd' || frase[j] == 'n' || frase[j] == 'x'){
					frase[posEscrita] = '3';
				}else if(frase[j] == 'J' || frase[j] == 'T' || frase[j] == 'e' || frase[j] == 'o' || frase[j] == 'y'){
					frase[posEscrita] = '4';
				}else if(frase[j] == 'D' || frase[j] == 'N' || frase[j] == 'X' || frase[j] == 'f' || frase[j] == 'p' || frase[j] == 'z'){
					frase[posEscrita] = '5';
				}else if(frase[j] == 'A' || frase[j] == 'K' || frase[j] == 'U' || frase[j] == 'g' || frase[j] == 'q'){
					frase[posEscrita] = '6';
				}else if(frase[j] == 'C' || frase[j] == 'M' || frase[j] == 'W' || frase[j] == 'h' || frase[j] == 'r'){
					frase[posEscrita] = '7';
				}else if(frase[j] == 'B' || frase[j] == 'L' || frase[j] == 'V' || frase[j] == 'i' || frase[j] == 's'){
					frase[posEscrita] = '8';
				}else if(frase[j] == 'H' || frase[j] == 'R' || frase[j] == 'j' || frase[j] == 't'){
					frase[posEscrita] = '9';
				}else{
					frase[posEscrita] = frase[j];
				}
				posEscrita++;
			}			
		}
		frase[posEscrita] = '\0';
		
		printf("%s\n", frase);

		i++;
	}

	return 0;
}
