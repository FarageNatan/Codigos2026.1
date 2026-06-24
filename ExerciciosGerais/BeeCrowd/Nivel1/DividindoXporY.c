#include <stdlib.h>
#include <stdio.h>

float divisao(float x, float y){
    return x / y;
}

int main(){
    int N = 0;
    int i = 0;
    scanf("%d", &N);
    while(i < N){
        float x = 0, y = 0, resultado = 0;
        scanf("%f %f", &x, &y);
        if((x > 0 && y > 0) || (x < 0 && y > 0) || (x > 0 && y < 0)){
            resultado = divisao(x, y); 
            printf("%.1f\n", resultado); 
        }else if(x == 0 && y > 0){
            printf("0.0\n");
        }else{
            printf("divisao impossivel\n");
        }
        i++;
    }
    return 0;
}