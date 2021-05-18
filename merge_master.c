#include <api.h>
#include <stdio.h>
#include <stdlib.h>
#include "merge.h"

Message msg[QDT];

int tam = (TAM / QDT);
int i;
int j;

void GerarVetor(int vet[QDT][tam]);
void GerarMsg(int vet[QDT][tam]);
void EnviaVetor();
void RecuperaVetor();
void OrganizaVetor(int vet[QDT][tam]);
void MostrarVetor(int vet[QDT][tam]);

int main(){
    int vetor[QDT][tam];

    GerarVetor(vetor);
    GerarMsg(vetor);
    printf("Vetor Gerado: \n");
    MostrarVetor(vetor);
    EnviaVetor();
    RecuperaVetor();
    OrganizaVetor(vetor);
    printf("\nVetor Ordenado: \n");
    MostrarVetor(vetor);

    return 0;
}

void GerarVetor(int vet[QDT][tam]){
    for(i = 0; i < QDT; i++){
        for(j = 0; j < tam; j++){
            vet[i][j] = rand() % 1000;
        }
    }
}

void GerarMsg(int vet[QDT][tam]){
    int lenght;
    for(i = 0; i < QDT; i++){
        msg[i].msg[0] = i;
        lenght = 1;
        for(j = 1; j <= tam; j++){
            msg[i].msg[j] = vet[i][j - 1];
            lenght++;
        }
        msg[i].length = lenght;
    }
}

void EnviaVetor(){
    Send(&msg[0], merge_0);
    Send(&msg[1], merge_1);
    Send(&msg[2], merge_2);
    Send(&msg[3], merge_3);
}

void RecuperaVetor(){
    Receive(&msg[0], merge_0);
    Receive(&msg[1], merge_1);
    Receive(&msg[2], merge_2);
    Receive(&msg[3], merge_3);    
}

void OrganizaVetor(int vet[QDT][tam]){
    for(i = 0; i < QDT; i++){
        for(j = 1; j <= tam; j++){
            vet[i][j - 1] = msg[i].msg[j];
        }
    }
}

void MostrarVetor(int vet[QDT][tam]){
    for(i = 0; i < QDT; i++){
        printf("Vetor %d [ ", i);
        for(j = 0; j < tam; j++){
            printf("%d ", vet[i][j]);
        }
        printf("]\n");
    }
}