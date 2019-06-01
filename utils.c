#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>
#include <mqueue.h>
#include "constants.h"

void list(){
    
    DIR * dir;
    struct dirent *folder;
    dir = opendir("/dev/mqueue/");
    
    if(dir){

        while((folder = readdir(dir))!=NULL){
             printf("%s\n", folder->d_name);       
        
        }
        closedir(dir);
    }else{
        printf("erro ao abrir o diretorio");
    }
}

char * name_chat_format(char * name){

    char * delimiter = (char*)malloc(sizeof(char)*20);
    strcat(delimiter, "/chat-");
    char * queue_name = name;
    strcat(delimiter, name);
    
    return delimiter;

}

void exit_msg(int a){
    pid_t pid = getpid();
    printf("Digite sair para encerrar o chat.\n");
    sleep(3);
    mq_unlink(queue_name);

    kill(pid, 9);
}