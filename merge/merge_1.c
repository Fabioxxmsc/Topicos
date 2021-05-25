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

    Echo("Escravo 1 iniciou");
    Receive(&msg, merge_master);
    Echo("Escravo 1 recebeu de master");

    if(msg.length <= 1){
        Echo("Escravo 1 retorna mensagem ao master");
        Send(&msg, merge_master);
        return 0;
    }

    int i;
    int vetor[msg.length - 1];
    int id = msg.msg[0];
    int tmp = 0;
    Message msg0;
    Message msg2;
    int status = NAO;

    for (i = 1; i <= msg.length; i++)
        vetor[i - 1] = msg.msg[i];

    do{
        Echo("Escravo 1 ordenando...");
        quicksort(vetor, 0, msg.length - 1);

        for (i = 0; i < msg.length; i++)
            msg.msg[i + 1] = vetor[i];

        if (status == NAO){
            Echo("Escravo 1 aguardando escravo 0...");
            Receive(&msg0, merge_0);
            Echo("Escravo 0 respondeu escravo 1");
        }

        if (msg0.msg[VALOR] < vetor[0]){

            status           = SIM;
            msg2.length      = 2;
            msg2.msg[STATUS] = NAO;
            msg2.msg[VALOR]  = vetor[msg.length - 1];

            Echo("Escravo 1 envia");
            Echo(itoa(msg2.msg[VALOR]));
            Echo("para escravo 2");

            Send(&msg2, merge_2);
            Echo("Escravo 1 aguardando escravo 2...");
            Receive(&msg2, merge_2);
            Echo("Escravo 2 respondeu escravo 1");

            if (msg2.msg[STATUS] == SIM){
                msg0.msg[STATUS] = SIM;

                Echo("Escravo 1 envia OK para escravo 0");
                Send(&msg0, merge_0);
                Echo("Escravo 1 envia para master");
                Send(&msg, merge_master);
                break;
            } else {
                Echo("Escravo 1 copia");
                Echo(itoa(msg2.msg[VALOR]));
                Echo("do escravo 2");
                vetor[msg.length - 1] = msg2.msg[VALOR];

                Echo("Escravo 1 ordenando...");
                quicksort(vetor, 0, msg.length - 1);

                for (i = 0; i < msg.length; i++)
                    msg.msg[i + 1] = vetor[i];

                if (msg0.msg[VALOR] >= vetor[0]){
                    tmp              = vetor[0];
                    vetor[0]         = msg0.msg[VALOR];
                    msg0.msg[VALOR]  = tmp;
                    msg0.msg[STATUS] = NAO;
                    status           = NAO;

                    Echo("Escravo 1 envia");
                    Echo(itoa(msg0.msg[VALOR]));
                    Echo("para escravo 0");
                    Send(&msg0, merge_0);                    
                }
            }
        } else {
            tmp              = vetor[0];
            vetor[0]         = msg0.msg[VALOR]; 
            msg0.msg[VALOR]  = tmp;
            msg0.msg[STATUS] = NAO;

            Echo("Escravo 1 envia");
            Echo(itoa(msg0.msg[VALOR]));
            Echo("para escravo 0");       
            Send(&msg0, merge_0);
        }

    } while (SIM);

    Echo("Escravo 1 finalizou");
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
