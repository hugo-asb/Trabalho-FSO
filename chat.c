#include <stdio.h>
#include <stdlib.h>
#include <mqueue.h>
#include <sys/stat.h>
#include <pthread.h>
#include <string.h>
#include "constants.h"
#include "chat.h"
#include "types.h"

#define MAX_SIZE 100

void *send_msg(){
   

    while(1){
        char * msg = (char*)malloc(sizeof(char)*500);
        char * from = (char*)malloc(sizeof(char)*10);
        char * by = (char*)malloc(sizeof(char)*10);
        char * content = (char*)malloc(sizeof(char)*MAX_SIZE);
        char * delimiter = (char*)malloc(sizeof(char)*20);
        
        scanf("%[^:]:%[^:]:%[^\n]", from, by, msg);
        
        strcat(delimiter, "/chat-");
        strcat(delimiter, by);

        if ((q_send = mq_open (delimiter, O_RDWR)) < 0){
            perror ("mq_open");
            printf("q_send");
            exit (1);
        }
        strcat(content, from);
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
    free(delimiter);
   }
}

void *receive_msg(void *msg){
    
    char msg_received[500];
    while(1){
        
        if((mq_receive (q_receive, msg_received, sizeof(msg_received), NULL)) < 0){
            perror("mq_receive");
            printf("mq_receive");
            exit(1);
        }

        printf("%s\n", msg_received);
    }
}

