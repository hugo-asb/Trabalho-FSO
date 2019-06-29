#include <stdio.h>
#include <dirent.h>
#include <stdlib.h>
#include <mqueue.h>
#include <sys/stat.h>
#include <pthread.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include "constants.h"
#include "chat.h"
#include "channel.h"
#include "types.h"
#include "string.h"
#include "utils.h"

#define MAX_SIZE 100

void * send_msg(char* from, char * by, char* msg){

    char * delimiter = (char*)malloc(sizeof(char)*20);
    char * content = (char*)malloc(sizeof(char)*MAX_SIZE);
    int flag_error = 1;
    strcat(delimiter, "/chat-");
    strcat(delimiter, by);
    if ((q_send = mq_open (delimiter, O_RDWR)) < 0){
        if(errno == 2){
            printf("UNKNOWNUSER %s\n", by);
            flag_error = -1;
        }
    }
        
    strcat(content, from);
    strcat(content, ": ");
    strcat(content, msg);

    struct timespec *time = (struct timespec*)malloc(sizeof(struct timespec));
    time->tv_sec = 30000;
    time->tv_nsec = 0;
    int tried = 1;
    if(flag_error>0){
        while(((mq_timedsend (q_send, content, strlen(content)+1, 0, time)) < 0)&&tried <4){
            printf("%d - ",tried);
            printf("Reenviando\n");
            sleep(3);
            tried ++;
        }
        if(tried == 4){
            printf("ERRO %s:%s:%s\n",from, by, msg);
        }
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
            char  * broad_cast_msg = (char*)malloc(sizeof(char)*500);
            strcat(broad_cast_msg, "Broadcast de ");
            strcat(broad_cast_msg, from);
            send_msg(broad_cast_msg, name, msg);
            }
        }
    }
}

void * handler_msg(){

    while(1){
        
        int command;
        scanf("%d", &command);
        if(command == 2){
            list();
        }else if(command == 3){
            exit_command();
        }else if(command == 1){
            char * msg = (char*)malloc(sizeof(char)*500);
            char * from = (char*)malloc(sizeof(char*)*10);
            char * by = (char*)malloc(sizeof(char)*10);
            scanf("%[^:]:%[^:]:%[^\n]", from, by, msg);
            if(strcmp(by, "all")==0){
                broadcast(from, msg);
            }else{
                send_msg(from, by, msg);
            }
        }else if(command == 4 ){
            char channel_name[20];
            scanf("%s", channel_name);
            create_channel(channel_name); 
        }
    }
}

void *receive_msg(){
    
    char msg_received[500];
    while(1){
        
        if((mq_receive (q_receive, msg_received, sizeof(msg_received), NULL)) < 0){
            perror("mq_receive");
            printf("mq_receive");
            exit(1);
        }
        printf("\t%s\n", msg_received);
    }
}

