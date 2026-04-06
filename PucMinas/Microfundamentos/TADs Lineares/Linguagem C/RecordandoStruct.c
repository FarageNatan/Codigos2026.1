#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct Ponto {
    float x;
    float y;
} Ponto;

float calculaDistancia(Ponto p1, Ponto p2){

    printf("X de p1: ");
    scanf("%f", &p1.x);
    printf("Y de p1: ");
    scanf("%f", &p1.y);

    printf("X de p2: ");
    scanf("%f", &p2.x);
    printf("Y de p2: ");
    scanf("%f", &p2.y);

    float distancia = sqrt(pow((p2.x - p1.x), 2.0) + pow((p2.y - p1.y), 2.0));

    return distancia;
}

float distanciaComPonteiro(Ponto* p1, Ponto* p2){
    printf("X de p1: ");
    scanf("%f", &p1->x);
    printf("Y de p1: ");
    scanf("%f", &p1->y);

    printf("X de p2: ");
    scanf("%f", &p2->x);
    printf("Y de p2: ");
    scanf("%f", &p2->y);

    float distancia = sqrt(pow((p2->x - p1->x), 2.0) + pow((p2->y - p1->y), 2.0));

    return distancia;
}

int main(){
    Ponto* p1 = malloc(sizeof(Ponto));
    Ponto* p2 = malloc(sizeof(Ponto));
    
    float distancia = distanciaComPonteiro(p1, p2);

    printf("%.2f\n", distancia);

    free(p1);
    free(p2);

    return 0;
}