#include <stdio.h>
#include <dirent.h>
#include <stdlib.h>
#include <mqueue.h>
#include <sys/stat.h>
#include <pthread.h>
#include <string.h>
#include "constants.h"
#include "chat.h"
#include "types.h"

#define MAX_SIZE 100

void * send_msg(char* from, char * by, char* msg){

    char * delimiter = (char*)malloc(sizeof(char)*20);
    char * content = (char*)malloc(sizeof(char)*MAX_SIZE);
    
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
    free(content);
    free(delimiter);
}

void * broadcast(char * from, char* msg){
    DIR *dir;
    struct dirent * folder;
    dir = opendir("/dev/mqueue");
    char * buffer = ".";
    char * buffer2 = "..";
    if(dir){
        while((folder = readdir(dir))!=NULL){
            if(strcmp(folder->d_name, buffer)!=0 && strcmp(folder->d_name, buffer2)!=0){
            char *name = folder->d_name;
            name +=5;
            send_msg(from, name, msg);
            }
        }
    }
        
}

void * handler_msg(){
   

    while(1){
        
        char * msg = (char*)malloc(sizeof(char)*500);
        char * from = (char*)malloc(sizeof(char)*10);
        char * by = (char*)malloc(sizeof(char)*10);
        
        scanf("%[^:]:%[^:]:%[^\n]", from, by, msg);
        char * all = "all";
        if(strcmp(by, all)==0){
            broadcast(from, msg);
        }else{
            send_msg(from, by, msg);
        }
        free(msg);
        free(from);
        free(by);
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

