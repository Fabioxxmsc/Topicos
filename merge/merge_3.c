#include <api.h>
#include <stdlib.h>

Message msg;

#define SIM 1
#define NAO 0

#define STATUS 0
#define VALOR 1

void quicksort(int values[], int began, int end);

int main(){
    Echo("Escravo 3 iniciou");
    Receive(&msg, merge_master);
    Echo("Escravo 3 recebeu de master");

    if (msg.length <= 1){
        Echo("Escravo 3 retorna mensagem ao master");
        Send(&msg, merge_master);
        return 0;
    }

    int i, temp;
    int vetor[msg.length - 1];
    int id = msg.msg[0];
    Message msgCom;

    for (i = 1; i < msg.length; i++)
        vetor[i - 1] = msg.msg[i];

    do{
        quicksort(vetor, 0, msg.length - 1);

        for (i = 1; i < msg.length; i++)
            msg.msg[i] = vetor[i - 1];
        
        Receive(&msgCom, merge_2);

        if (msgCom.msg[VALOR] <= vetor[0]){
            msgCom.length = 2;
            msgCom.msg[STATUS] = SIM;

            Echo("Escravo 3 envia OK para escravo 2");
            Send(&msgCom, merge_2);

            Echo("Escravo 3 envia para master");
            Send(&msg, merge_master);
            break;
        } else {
            temp               = vetor[0];
            vetor[0]           = msgCom.msg[VALOR];
            msgCom.msg[VALOR]  = temp;
            msgCom.msg[STATUS] = NAO;
            Send(&msgCom, merge_2);
        }
    } while (SIM);

    Echo("Escravo 3 finalizou");
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
