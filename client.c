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
//КЛИЕНТ
int main()
{
    struct 
    {
        long mestype;
        int mes;
    } messageto;
    struct 
    {
        long mestype;
        int res[2];
    } messagefrom;
    key_t key = ftok("f1.txt", 'r');
    int mesid = msgget(key, 0666 | IPC_CREAT );
    int mes;
    printf("Добро пожаловать в игру 'Быки и Коровы'!\nПравила игры: угадать четырехзначное число, используя цифры от 1 до 6\n");
    
    while(1){
    printf("Введите число: ");
    scanf("%d", &mes);
    messageto.mes = mes;
    messageto.mestype = 1;
    msgsnd(mesid, &messageto, sizeof(messageto), 0);
    msgrcv(mesid, &messagefrom, sizeof(messagefrom), 2, 0);
    if (messagefrom.res[1] == 0) 
    {
        printf("Поздравляем! Вы угадали число: %d \n", mes);
        break;
    }
    else if (messagefrom.res[1] > 0)
    {
        printf("Быки: %d Коровы: %d\n", messagefrom.res[0], messagefrom.res[1]);
    
    }
    else if ((messagefrom.res[1] < 0))
    {
        printf("У Вас не получилось угадать число. Ответ : %d\n", messagefrom.res[0]);
        break;
    }
    }
    msgctl(mesid, IPC_RMID, 0);
    return 0;
}