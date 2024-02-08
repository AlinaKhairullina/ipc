#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <time.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/ipc.h>
#include <sys/msg.h>
//СЕРВЕР
int main()
{
    struct 
    {
        long mestype;
        int mes;
    } messagefrom;

    struct 
    {
        long mestype;
        int res[2];
    } messageto;
    key_t key = ftok("f1.txt", 'r');
    int mesid = msgget(key, 0666 | IPC_CREAT );
    long ltime, stime;
    ltime = time(NULL);
    stime = (unsigned int)ltime/2;
    srand(stime);
   int dgt1 = (rand()%6 + 1);
    int dgt2 = (rand()%6 + 1);;
    while(dgt1 == dgt2) {
      dgt2 = (rand()%6 + 1);; 
      }
    int dgt3 = (rand()%6 + 1);
    while(dgt3 == dgt2 || dgt3 == dgt1){
      dgt3 = (rand()%6 + 1); 
     }
    int dgt4 = (rand()%6 + 1);;
    while(dgt4 == dgt3 || dgt4 == dgt2 || dgt4 == dgt1){
       dgt4 = (rand()%6 + 1);;
       }
    int dgt = dgt1 * 1000 + dgt2 * 100 + dgt3*10 + dgt4;
    printf("Компьютер сгенерировал число: %d\n", dgt);
    int n = 0;
    while(n < 6){
        int b = 0, k = 0; //быки и коровыы
        msgrcv(mesid, &messagefrom, sizeof(messagefrom), 1, 0);
        if (messagefrom.mes == dgt) 
        {
            printf("RIGHT NUMBER\n");
            messageto.res[0] = 0;
            messageto.res[1] = 0;
            messageto.mestype = 2;
            msgsnd(mesid, &messageto, sizeof(messageto), 0);
            return 0;
        }
        else
        {
            int i, j, t, l;
            i = messagefrom.mes/1000;
            j = messagefrom.mes/100%10;
            t = messagefrom.mes/10%10;
            l = messagefrom.mes%10;
            k += (i == dgt1) || (j == dgt1) || (t == dgt1) || (l == dgt1);
            k += (i == dgt2) || (j == dgt2) || (t == dgt2) || (l == dgt2);
            k += (i == dgt3) || (j == dgt3) || (t == dgt3) || (l == dgt3);
            k += (i == dgt4) || (j == dgt4) || (t == dgt4) || (l == dgt4);
            b += i == dgt1;b += j == dgt2;b += t == dgt3;b += l == dgt4;
            messageto.res[0] = b;
            messageto.res[1] = k;
            messageto.mestype = 2;
            n++;
            msgsnd(mesid, &messageto, sizeof(messageto), 0);
        }

    }
    msgrcv(mesid, &messagefrom, sizeof(messagefrom), 1, 0);
    messageto.res[0] = dgt;
    messageto.res[1] = -1;
    messageto.mestype = 2;
    msgsnd(mesid, &messageto, sizeof(messageto), 0);
    return 0;
}