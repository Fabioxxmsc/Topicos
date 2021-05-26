#include <api.h>
#include <stdlib.h>

#define TAM 8
#define QDT 4
#define tam TAM / QDT

#define SIM 1
#define NAO 0

#define STATUS 0
#define VALOR 1

// MSG_SIZE

unsigned int slaves[QDT] = {merge_0, merge_1, merge_2, merge_3};

Message msg[QDT];

int i;
int j;

void ZerarMsg();
void MostraVetor(int vet[TAM]);
void GerarVetor(int vet[TAM]);
void GerarMsg(int vet[TAM]);
void EnviaVetor();
void RecuperaVetor();
void OrganizaVetor(int vet[TAM]);

int main(){
    int vetor[TAM];

    ZerarMsg();
    GerarVetor(vetor);
    MostraVetor(vetor);
    GerarMsg(vetor);
    EnviaVetor();
    RecuperaVetor();
    OrganizaVetor(vetor);
    MostraVetor(vetor);

    return 0;
}

void ZerarMsg(){
    for (i = 0; i < QDT; i++)
      msg[i].length = 0;
}

void GerarVetor(int vet[TAM]){
    for(i = 0; i < TAM; i++){
        if (i % 2 == 0)
            vet[i] = (i + 2) * 2;
        else
            vet[i] = (i + 3) * 3;
    }
}

void GerarMsg(int vet[TAM]){
    int index_vet = 0;
    for(i = 0; i < QDT; i++){
        msg[i].msg[0] = i;
        msg[i].length++;

        for(j = 1; j <= tam; j++){
            msg[i].msg[j] = vet[index_vet];
            msg[i].length++;
            index_vet++;
        }
    }
}

void EnviaVetor(){
    for (i = 0; i < QDT; i++){
        Echo("Enviando vetor escravo");
        Echo(itoa(i));
        Send(&msg[i], slaves[i]);
    }
}

void RecuperaVetor(){
    for (i = QDT - 1; i >= 0; i--){
        Echo("Aguardando Vetor");
        Echo(itoa(i));        
        Receive(&msg[i], slaves[i]);
        Echo("Recebido Vetor");
    }
}

void OrganizaVetor(int vet[TAM]){
    int index_vet = 0;
    for(i = 0; i < QDT; i++){
        for(j = 1; j <= tam; j++){
            vet[index_vet] = msg[i].msg[j];
            index_vet++;
        }
    }
}

void MostraVetor(int vet[TAM]){
    Echo("Vetor");
    for(i = 0; i < TAM; i++){
        Echo(itoa(vet[i]));
    }
}