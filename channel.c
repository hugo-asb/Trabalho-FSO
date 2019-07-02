#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <mqueue.h>
#include <sys/stat.h>
#include <pthread.h>
#include "constants.h"
#include "types.h"
#include "chat.h"
#include "string_utils.h"
#include "channel.h"

User_channel users[50];
int count = 0;

#define MAX_SIZE 100

void create_channel(char * channel_name){
    
    channel = channel_name; 
    char * channel_delimiter = (char*)malloc(sizeof(char)*20);
    
    strcat(channel_delimiter, "/canal-");
    strcat(channel_delimiter, channel_name);
    mode_t  default_umask = umask(0000);
    struct  mq_attr attr;
    attr.mq_maxmsg = 10;
    attr.mq_msgsize = 100;
    attr.mq_flags = 0;
    if((q_receive_channel = mq_open(channel_delimiter, O_RDWR|O_CREAT, 0622, &attr))<0){
        perror("mq_open");
        exit(1);
    
    }else{
        printf("sala criada como sucesso\n");
        
    }
    umask(default_umask);
}

void add_to_channel(char * name){
    
    User_channel new_user;
    new_user.name = name;
    users[count] = new_user;
    count ++;
}
/*
void remove(){
    
}
*/

void * send_msg_channel(char * from, char * msg){
    
    char * content = (char*)malloc(sizeof(char)*500);
    char * channel_name = (char*)malloc(sizeof(char)*20);    
    
   
    strcat(content, "#");
    strcat(content, channel);
    strcat(content, ":");
    strcat(content, from);
    strcat(content, ":");
    //channel name
    strcat(content, msg);
    strcat(channel_name,"/canal-");
    strcat(channel_name, channel);
    printf("conteudo = %s", content); 
    if((q_send_channel = mq_open(channel_name, O_RDWR))<0){
        
        perror("mq_send");
        printf("channel_send");
    
    }
    if((mq_send(q_send_channel, content, strlen(content)+1,0))<0){
        perror("mq_send");
        exit(1);
    }
}

void * channel_receive(){   
   
    char msg_received[500];
    char * channel_name = (char*)malloc(sizeof(char)*20);
    while(1){
        if(mq_receive(q_receive_channel, msg_received, sizeof(msg_received), NULL)<0){
            perror("mq_receive");
            printf("mq_receive");
            exit(1);
        
        }
        printf("\n%s\n", msg_received);
    
    if(strstr(msg_received, "join")!= NULL){
         char * name_to_send = (char*)malloc(sizeof(char)*20);
         
         printf("message == %s\n", msg_received);
         char * name  = find(msg_received, 0);
         
         strcat(name_to_send, name);
         add_to_channel(name_to_send); 
         int i; 
         for(i =0 ; i< count; i++){

            char * name = users[i].name;
            send_msg_channel(name, "foi adicionado ao canal!\n");      
         }
 
    }
    /*
    else if((strstr(msg_received, "leave")!= NULL)){
         //remove();
    }else{
        // send msg to all in the channel 
        int i = 0;  
        for(i = 0 ; i< count; i++){      
            char * name = users[i].name;
            char * queue_name = format_channel_name(name);
            send_msg_channel(queue_name, "teste");      
        }
    }
    */
    }
}

char * format_channel_name ( char * name){
    char * delimiter = (char *)malloc(sizeof(char)*20);
    delimiter = "chat-";
    strcat(delimiter, name);
    return delimiter;
}
