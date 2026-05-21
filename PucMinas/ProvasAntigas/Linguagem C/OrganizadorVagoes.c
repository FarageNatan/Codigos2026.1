#include <stdio.h>
#include <stdlib.h>

void swap(int* array, int i, int j){
    int tmp = array[i];
    array[i] = array[j];
    array[j] = tmp;
}

int main(){
    int N;
    scanf("%d", &N);
    int i = 0;
    while(i < N){
        int L;
        scanf("%d", &L);
        int* trem = (int*) malloc(L * sizeof(int));
        
        for(int i = 0; i < L; i++){
            scanf("%d", &trem[i]);
        }

        int swaps = 0;
        for(int i = L - 1; i > 0; i--){
            for(int j = 0; j < i; j++){
                if(trem[j] > trem[j + 1]){
                    swap(trem, j, j + 1);
                    swaps++;
                }
            }
        }

        printf("Optimal train swapping takes %d swaps\n", swaps);

        free(trem);

        i++;
    }

    return 0;
}