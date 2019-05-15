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

   
    printf("digite o nome da fila\n");
    scanf("%[^\n]", queue_name);
    printf("digite o a ser recebido\n");
    scanf(" %[^\n]", destination);
    msg->destination = destination; 
  
    pthread_create(&send, NULL, send_msg, (void*)queue_name);
    pthread_create(&receive, NULL, receive_msg, (void*) msg);
    pthread_join (receive, &thread_res);
}
