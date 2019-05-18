#include <stdio.h>
#include <stdlib.h>
#include <mqueue.h>
#include <sys/stat.h>
#include <pthread.h>
#include <string.h>
#include "constants.h"
#include "chat.h"
#include "types.h"


#define QUEUE "/josue"

#define MAX_SIZE 100

void *send_msg(){
   
   //char delimiter[20] = "/chat-";

    while(1){
        char * msg = (char*)malloc(sizeof(char)*500);
        char * from = (char*)malloc(sizeof(char)*10);
        char * by = (char*)malloc(sizeof(char)*10);
        char * content = (char*)malloc(sizeof(char)*MAX_SIZE);
        
        scanf("%[^:]:%[^:]:%[^\n]", from, by, msg);
        
        if ((q_send = mq_open ("/josue", O_RDWR)) < 0){
            perror ("mq_open");
            printf("q_send");
            exit (1);
        }
        strcat(content, by);
        strcat(content, ":");
        strcat(content, msg);
        if((mq_send (q_send, content, strlen(content)+1, 0)) < 0){
            perror("mq_send");
            printf("send");
            exit(1);
    
    }
   
    free(msg);
    free(from);
    free(by);
    free(content);
   }
}

void *receive_msg(void *msg){
    
    char msg_received[500];

    struct mq_attr attr;
    attr.mq_maxmsg = 100;
    attr.mq_msgsize = strlen(msg_received);
    attr.mq_flags = 0;

    if ((q_receive = mq_open ("/josue", O_RDWR|O_CREAT, 0666 , &attr)) < 0){
        perror ("mq_open");
        printf("q_receive\n"); 
        exit (1);
    }
    
    while(1){
        
        if((mq_receive (q_receive, msg_received, sizeof(msg_received), NULL)) < 0){
            perror("mq_receive");
            printf("mq_receive");
            exit(1);
        }

        printf("recebido = %s\n", msg_received);
    }
}

