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

    Echo("Escravo 2 iniciou");
    Receive(&msg, merge_master);
    Echo("Escravo 2 recebeu de master");

    if(msg.length <= 1){
        Echo("Escravo 2 retorna mensagem ao master");
        Send(&msg, merge_master);
        return 0;
    }

    int i;
    int vetor[msg.length - 1];
    int id = msg.msg[0];
    int tmp = 0;
    Message msg1;
    Message msg3;
    int status = NAO;

    for (i = 1; i <= msg.length; i++)
        vetor[i - 1] = msg.msg[i];

    do{
        Echo("Escravo 2 ordenando...");
        quicksort(vetor, 0, msg.length - 1);

        for (i = 0; i < msg.length; i++) {
            msg.msg[i + 1] = vetor[i];
        }

        if (status == NAO) {
            Echo("Escravo 2 aguardando escravo 1...");
            Receive(&msg1, merge_1);
            Echo("Escravo 1 respondeu escravo 2...");
        }

        if (msg1.msg[VALOR] < vetor[0]) {

            status           = SIM;
            msg3.length      = 2;
            msg3.msg[STATUS] = NAO;
            msg3.msg[VALOR]  = vetor[msg.length - 1];

            Echo("Escravo 2 enviando");
            Echo(itoa(msg3.msg[VALOR]));
            Echo("para escravo 3");

            Send(&msg3, merge_3);
            Echo("Escravo 2 aguardando escravo 3...");
            Receive(&msg3, merge_3);
            Echo("Escravo 3 respondeu escravo 2");

            if (msg3.msg[STATUS] == SIM){
                msg1.msg[STATUS] = SIM;

                Echo("Escravo 2 envia OK para escravo 1");
                Send(&msg1, merge_1);
                Echo("Escravo 2 envia para master");
                Send(&msg, merge_master);
                break;
            } else {
                Echo("Escravo 2 copia");
                Echo(itoa(msg3.msg[VALOR]));
                Echo("do escravo 3");
                vetor[msg.length - 1] = msg3.msg[VALOR];

                Echo("Escravo 2 ordenando...");
                quicksort(vetor, 0, msg.length - 1);

                for (i = 0; i < msg.length; i++)
                    msg.msg[i + 1] = vetor[i];

                if (msg1.msg[VALOR] >= vetor[0]){                    
                    tmp              = vetor[0];
                    vetor[0]         = msg1.msg[VALOR];
                    msg1.msg[VALOR]  = tmp;
                    msg1.msg[STATUS] = NAO;
                    status           = NAO;

                    Echo("Escravo 2 envia");
                    Echo(itoa(msg1.msg[VALOR]));
                    Echo("para escravo 1");
                    Send(&msg1, merge_1);                    
                }
            }
        } else {
            Echo("Escravo 2 copia");
            Echo(itoa(msg1.msg[VALOR]));
            Echo("do escravo 1");

            tmp              = vetor[0];
            vetor[0]         = msg1.msg[VALOR]; 
            msg1.msg[VALOR]  = tmp;
            msg1.msg[STATUS] = NAO;                      

            Echo("Escravo 2 envia");
            Echo(itoa(msg1.msg[VALOR]));
            Echo("para escravo 1");
            Send(&msg1, merge_1);
        }

    } while (SIM);

    Echo("Escravo 2 finalizou");
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
