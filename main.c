#include <stdio.h>
#include <stdlib.h>
#include <mqueue.h>
#include <sys/stat.h>
#include <pthread.h>
#include <string.h>
#include "chat.h"
#include "constants.h"
#include "types.h"

int main(int argc, char *argv[]){
    
    msg_params_t * msg;
    pthread_t receive, send;
    void * thread_res;
    
    msg = (msg_params_t*)malloc(sizeof(msg_params_t));
    char msg_received[500];

    
    struct mq_attr attr;
    attr.mq_maxmsg = 10;
    attr.mq_msgsize = 100;
    attr.mq_flags = 0;
 
    char * delimiter = (char*)malloc(sizeof(char)*20);
    strcat(delimiter, "/chat-");
    char * queue_name = argv[1];
    strcat(delimiter, queue_name);
    if ((q_receive = mq_open (delimiter, O_RDWR|O_CREAT, 0666 , &attr)) < 0){
        perror ("mq_open");
        printf("q_receive\n"); 
        exit (1);
    }

    pthread_create(&send, NULL, send_msg, NULL);
    
    pthread_create(&receive, NULL, receive_msg, (void*) msg);
    pthread_join (receive, &thread_res);
}
