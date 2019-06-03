#include <stdio.h>
#include <stdlib.h>
#include <mqueue.h>
#include <sys/stat.h>
#include <pthread.h>
#include <string.h>
#include <signal.h>
#include "chat.h"
#include "constants.h"
#include "types.h"
#include "utils.h"



int main(int argc, char *argv[]){
    
    pthread_t receive, send;
    void * thread_res;
    
    struct mq_attr attr;
    attr.mq_maxmsg = 10;
    attr.mq_msgsize = 100;
    attr.mq_flags = 0;
    
    queue_name = name_chat_format(argv[1]);

    char * all = "all";
    if(strcmp(argv[1], all)==0){
        printf("Erro: O nome do usuário não pode ser \"all\".\n");
        return 0;
    };

    signal(SIGINT, exit_msg);

    mode_t default_umask = umask(0000);
    if ((q_receive = mq_open (queue_name, O_RDWR|O_CREAT, 0666 , &attr)) < 0){
        perror ("mq_open");
        printf("q_receive\n"); 
        exit (1);
    }
    umask(default_umask);

    pthread_create(&send, NULL, handler_msg, NULL);
    
    pthread_create(&receive, NULL, receive_msg, NULL);
    pthread_join (receive, &thread_res);
}

