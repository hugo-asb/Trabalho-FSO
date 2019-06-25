#include "constants.h"
#include <string.h>
#include <mqueue>
#include <sys/stat.h>
#include "types.h"
#include "chat.h"

User_channel users[50];
int count = 0;

#define MAX_SIZE 100

void create_channel(char * channel_name){
    
    char * channel_delimiter = "/canal-";
    strcat(channel_delimiter, channel_name);
    mode_t  default_umask = umask(0000);
    struct  mq_attr attr.
    attr.mq_maxmsg = 10;
    attr.mq_msgsiz = 100;
    attr.mq_flags = 0;
    if((q_channel = mq_open(channel_delimiter, O_RDWR|OCREAT, 0622, &attr))<0){
        perror("mq_open");
        exit(1);
    
    }
    umask(default_umask);
}

void add_to_channel(char * name){
    
    User_channel new_user.name = name;
    users[count] = new_user;
    count ++;

}

void remove(){
    count--;
}

void *send_msg_channel(char * from, char * msg){
    
    char * content = (char*)malloc(sizeof(char)*MAX_SIZE);
    //char * delimiter = (char*)malloc(sizeof(char)*20);
    
    strcat(content, from);
    strcat(content, ": ");
    strcat(content, "#");
    //channel name
    strcat(content, );
    strcat(content, msg);

    if((q_send_channel = mq_open("channel", O_RDWR))<0){
        
        perror("mq_send");
        printf("mq_send");
    
    }
    if((mq_send(q_send_channel, (void*)&msg, sizeof(msg),0))<0){
        perror("mq_send");
        exit(1);
    }

}

void * channel_receive(){   
   
    char msg_received[500];
    
    while(1){
        if(mq_receive(,msg_received, sizeof(msg_received))<0){
            perror("mq_receive");
            printf("mq_receive");
            exit(1);
        }
    }
    
    if(strstr(msg_receive, "join")!= NULL){
         char * name  = find(msg_receive, 0);
         add_to_channel(name);
    }else if((strstr(msg_receive, "leave")!= NULL)){
         remove();
    }else{
        // send msg to all in the channel 
        int i = 0;  
        for(i = 0 ; i< count; i ++){     
            
            char * name = users[i].name;
    
        }
 
    }
    
  }
