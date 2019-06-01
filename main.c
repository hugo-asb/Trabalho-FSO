#include <stdio.h>
#include <stdlib.h>
#include <mqueue.h>
#include <sys/stat.h>
#include <pthread.h>
#include <string.h>
#include "chat.h"
#include "constants.h"
#include "types.h"
#include "utils.h"

int main(int argc, char *argv[]){
    
    pthread_t receive, send;
    void * thread_res;
    
    struct mq_attr attr;
    attr.mq_maxmsg = 1;
    attr.mq_msgsize = 100;
    attr.mq_flags = 0;
    
   char * queue_name = name_chat_format(argv[1]);

    if ((q_receive = mq_open (queue_name, O_RDWR|O_CREAT, 0666 , &attr)) < 0){
        perror ("mq_open");
        printf("q_receive\n"); 
        exit (1);
    }

    pthread_create(&send, NULL, handler_msg, NULL);
    
    pthread_create(&receive, NULL, receive_msg, NULL);
    pthread_join (receive, &thread_res);
}

