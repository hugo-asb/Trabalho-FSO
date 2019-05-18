#include <stdio.h>
#include <stdlib.h>
#include <mqueue.h>
#include <sys/stat.h>
#include <pthread.h>
#include "chat.h"
#include "constants.h"
#include "types.h"

int main(){
    
    msg_params_t * msg;
    pthread_t receive, send;
    void * thread_res;
    
    msg = (msg_params_t*)malloc(sizeof(msg_params_t));
    char queue_name[10];
    char destination[10];
    /*
    if(q_receive = mq_open("/josue",O_RDWR|O_CREAT, 0666, NULL)<0){
        perror("mq_open");
        exit(1);
    }
    */
    pthread_create(&send, NULL, send_msg, NULL);
    
    pthread_create(&receive, NULL, receive_msg, (void*) msg);
    pthread_join (receive, &thread_res);
}
