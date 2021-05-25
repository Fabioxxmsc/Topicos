#include <api.h>
#include <stdlib.h>

#define TAM 12
#define QDT 4
#define tam TAM / QDT

#define SIM 1
#define NAO 0

#define ID 0

#define STATUS 0
#define VALOR 1

Message msg[QDT];

int i;
int j;

void MostraVetor(int vet[QDT][tam]);
void GerarVetor(int vet[QDT][tam]);
void GerarMsg(int vet[QDT][tam]);
void EnviaVetor();
void RecuperaVetor();
void OrganizaVetor(int vet[QDT][tam]);

int main(){
    int vetor[QDT][tam];

    GerarVetor(vetor);
    MostraVetor(vetor);
    GerarMsg(vetor);
    EnviaVetor();
    RecuperaVetor();
    OrganizaVetor(vetor);
    Echo("\nVetor Ordenado: \n");
    MostraVetor(vetor);

    return 0;
}

void GerarVetor(int vet[QDT][tam]){
    vet[0][0] = 11;
    vet[0][1] = 10;
    vet[0][2] = 9;
    vet[1][0] = 8;
    vet[1][1] = 7;
    vet[1][2] = 6;
    vet[2][0] = 5;
    vet[2][1] = 4;
    vet[2][2] = 3;
    vet[3][0] = 2;
    vet[3][1] = 1;
    vet[3][2] = 0;
    //for(i = 0; i < QDT; i++){
    //    for(j = 0; j < tam; j++){
    //        vet[i][j] = (i + j + 1) * 3;
    //    }
   // }
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
    Echo("Enviando vetor escravo 0");
    Send(&msg[0], merge_0);
    Echo("Enviando vetor escravo 1");
    Send(&msg[1], merge_1);
    Echo("Enviando vetor escravo 2");
    Send(&msg[2], merge_2);
    Echo("Enviando vetor escravo 3");
    Send(&msg[3], merge_3);
}

void RecuperaVetor(){
    Echo("Aguardando Vetor 3...");
    Receive(&msg[3], merge_3);
    Echo("Recebido Vetor 3");

    Echo("Aguardando Vetor 2...");
    Receive(&msg[2], merge_2);
    Echo("Recebido Vetor 2");

    Echo("Aguardando Vetor 1...");
    Receive(&msg[1], merge_1);            
    Echo("Recebido Vetor 1");

    Echo("Aguardando Vetor 0...");
    Receive(&msg[0], merge_0);
    Echo("Recebido Vetor 0");
}

void OrganizaVetor(int vet[QDT][tam]){
    for(i = 0; i < QDT; i++){
        for(j = 1; j <= tam; j++){
            vet[i][j - 1] = msg[i].msg[j];
        }
    }
}

void MostraVetor(int vet[QDT][tam]){
    Echo("Vetor: ");
    for(i = 0; i < QDT; i++){
        for(j = 1; j <= tam; j++){
            Echo(itoa(vet[i][j]));
        }
    }
}