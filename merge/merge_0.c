#include <api.h>
#include <stdlib.h>

Message msg;

#define TAM 12
#define QDT 4
#define tam TAM / QDT

#define SIM 1
#define NAO 0

#define ID 0

#define STATUS 0
#define VALOR 1

void quicksort(int values[], int began, int end);

int main(){
    Echo("Escravo 0 iniciou");
    Receive(&msg, merge_master);
    Echo("Escravo 0 recebeu de master");

    if(msg.length <= 1){
        Echo("Escravo 0 retorna mensagem ao master");
        Send(&msg, merge_master);
        return(NAO);
    }

    int i;
    int vetor[msg.length - 1];
    int id = msg.msg[0];
    Message msg1; 

    for (i = 1; i <= msg.length; i++)
        vetor[i - 1] = msg.msg[i];

    do{
        Echo("Escravo 0 ordenando...");
        quicksort(vetor, 0, msg.length - 1);

        for (i = 0; i < msg.length; i++)
            msg.msg[i + 1] = vetor[i];

        msg1.length = 2;
        msg1.msg[STATUS] = NAO;
        msg1.msg[VALOR] = vetor[msg.length - 1];

        Echo("Escravo 0 envia");
        Echo(itoa(msg1.msg[VALOR]));
        Echo("para escravo 1");

        Send(&msg1, merge_1);

        Echo("Escravo 0 aguardando resposta do escravo 1...");
        Receive(&msg1, merge_1);
        Echo("Escravo 1 respondeu escravo 0");

        if (msg1.msg[STATUS] == SIM){
            Echo("Escravo 0 envia para master");
            Send(&msg, merge_master);
            break;
        }
        Echo("Escravo 0 copiando");
        Echo(itoa(msg1.msg[VALOR]));
        Echo("do escravo 1");
        vetor[msg.length - 1] = msg1.msg[VALOR];
        
    } while (SIM);

    Echo("Escravo 0 finalizou");
    return 0;
}

void quicksort(int values[], int began, int end)
{
    int i, j, pivo, aux;
    i = began;
    j = end-1;
    pivo = values[(began + end) / 2];
    while(i <= j)
    {
        while(values[i] < pivo && i < end)
        {
            i++;
        }
        while(values[j] > pivo && j > began)
        {
            j--;
        }
        if(i <= j)
        {
            aux = values[i];
            values[i] = values[j];
            values[j] = aux;
            i++;
            j--;
        }
    }
    if(j > began)
        quicksort(values, began, j+1);
    if(i < end)
        quicksort(values, i, end);
}
