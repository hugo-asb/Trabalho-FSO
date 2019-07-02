#include <stdio.h>
#include <stdlib.h>
#include <mqueue.h>
#include <sys/stat.h>
#include <pthread.h>
#include <string.h>
#include <signal.h>
#include "chat.h"
#include "channel.h"
#include "constants.h"
#include "types.h"
#include "utils.h"


int main(int argc, char *argv[]){
    
    pthread_t receive, send, channel_receive_msg;
    void * thread_res;
    void * channel_res;
    
    struct mq_attr attr;
    attr.mq_maxmsg = 10;
    attr.mq_msgsize = 100;
    attr.mq_flags = 0;
    
    queue_name = name_chat_format(argv[1]);
    count_ = 0;
    char * all = "all";
    if(strcmp(argv[1], all)==0){
        printf("Erro: O nome do usuário não pode ser \"all\".\n");
        return 0;
    };

    signal(SIGINT, exit_msg);

    mode_t default_umask = umask(0000);
    if ((q_receive = mq_open (queue_name, O_RDWR|O_CREAT, 0622 , &attr)) < 0){
        perror ("mq_open");
        printf("q_receive\n"); 
        exit (1);
    }
    create_channel(argv[2]);
    umask(default_umask);
    print_initial_menu();


    pthread_create(&send, NULL, handler_msg, NULL);
    pthread_create(&channel_receive_msg, NULL, channel_receive, NULL);
    pthread_create(&receive, NULL, receive_msg, NULL);
    pthread_join (receive, &thread_res);
    pthread_join (channel_receive_msg, &channel_res);
    
}

