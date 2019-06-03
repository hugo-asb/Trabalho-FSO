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
#include "string.h"
#include "utils.h"
#include <errno.h>
#include <unistd.h>

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
    strcat(content, ":");
    strcat(content, msg);
    

    struct timespec *time = (struct timespec*)malloc(sizeof(struct timespec));
    time->tv_sec = 30000;
    time->tv_nsec = 0;
    int tried = 1;
    if(flag_error>0){
        while(((mq_timedsend (q_send, content, strlen(content)+1, 0, time)) < 0)&&tried <4){
            printf("Reenviando\n");
            printf("%d\n",tried);
            sleep(3);
            tried ++;
            printf("%d",errno);
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
            send_msg(from, name, msg);
            }
        }
    }
        
}

void * handler_msg(){
   

    while(1){
        
        char * chat_content = read_message();
        char * list_ = "list\n";
        char * exit_ = "sair\n";
        if(strcmp(chat_content, list_)==0){
            list();
        } else if(strcmp(chat_content, exit_)==0){
            exit_command();
        }else{
            Msg * msg = get_attrs_msg(chat_content);
            char * all = "all";
            if(strcmp(msg->sender, all)==0){
                broadcast(msg->sender, msg->content);
            }else{
                send_msg(msg->sender, msg->receive, msg->content);
            }
        }
        printf("acabou\n");
        free(chat_content);
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

        printf("%s\n", msg_received);
    }
}

