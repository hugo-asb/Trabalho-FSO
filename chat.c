#include <stdio.h>
#include <stdlib.h>
#include <mqueue.h>
#include <sys/stat.h>
#include <pthread.h>
#include "constants.h"
#include "chat.h"
#include "types.h"

void *send_msg(void* queue_name){
    int msg;
  
    char * name = (char*)queue_name;
    if ((q_send = mq_open (name, O_RDWR)) < 0){
        perror ("mq_open");
        exit (1);
    }

    while(1){

        printf("Digite a msg: " );
        scanf("%d", &msg);

        if((mq_send (q_send, (void*) &msg, sizeof(msg), 0)) < 0){
            perror("mq_send");
            exit(1);
        }
        printf("Send msg: %d \n", msg);
    }
}

void *receive_msg(void *msg){
    
    msg_params_t * params_received = (msg_params_t*)msg;
    int *msg_received = params_received->value;
    
    struct mq_attr attr;
    attr.mq_maxmsg = 10;
    attr.mq_msgsize = sizeof(msg);
    attr.mq_flags = 0;
   
    if ((q_receive = mq_open (params_received->destination, O_RDWR|O_CREAT, 0666, &attr)) < 0){
        perror ("mq_open");
        exit (1);
    }
 
    while(1){
        if((mq_receive (q_receive, (void*) &msg_received, sizeof(msg_received), 0)) < 0){
            perror("mq_open");
            exit(1);
        }

        printf("Received msg: %d \n", msg_received);
    }
}

