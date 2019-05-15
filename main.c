#include <stdio.h>
#include <stdlib.h>
#include <mqueue.h>
#include <sys/stat.h>
#include <pthread.h>
#include "chat.h"
#include "constants.h"

int main(){
    
    int *msg;
    struct mq_attr attr;
    pthread_t receive, send;
    void * thread_res;
    
    msg = (int*)malloc(sizeof(int));
    char queue_name[10];

    attr.mq_maxmsg = 10;
    attr.mq_msgsize = sizeof(msg);
    attr.mq_flags = 0;
    
    printf("digite o nome da fila\n");
    scanf("%[^\n]", queue_name);
    
    if ((q_receive = mq_open (queue_name, O_RDWR|O_CREAT, 0666, &attr)) < 0){
        perror ("mq_open");
        exit (1);
    }

    pthread_create(&send, NULL, send_msg, NULL);
    pthread_create(&receive, NULL, receive_msg, (void*) msg);
    pthread_join (receive, &thread_res);
}
