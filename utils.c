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
    char * buffer = ".";
    char * buffer2 = "..";
    if(dir){
        printf("\n------------------------\n");    
        printf("     Pessoas Online\n");
        printf("------------------------\n");
        while((folder = readdir(dir))!=NULL){
            if(strcmp(folder->d_name, buffer)!=0 && strcmp(folder->d_name, buffer2)!=0){
            char *name = folder->d_name;
            name +=5;
            printf(" - %s\n", name);       
            }
        }
    }
    printf("------------------------\n\n");
}

char * name_chat_format(char * name){

    char * delimiter = (char*)malloc(sizeof(char)*20);
    strcat(delimiter, "/chat-");
    char * queue_name = name;
    strcat(delimiter, name);
    
    return delimiter;

}

void exit_msg(int a){
    printf("Digite sair para encerrar o chat.\n");
}

void exit_command(){
    pid_t pid = getpid();
    mq_unlink(queue_name);
    printf("\nChat finalizado!\n");
    kill(pid, 9);
}

void print_initial_menu(){
    printf("-------------------------------------------------------------------------\n");    
    printf("\t\tO chat foi iniciado.\n");
    printf("-------------------------------------------------------------------------\n");
    printf("- Use o comando \"1\" para enviar uma mensagem para alguem.\n");
    printf("- Use o camando \"2\" para ver as pessoas que estão online.\n");
    printf("- Use o camando \"3\" para encerrar o chat.\n");
    printf("- Use o camando \"4\" para criar uma sala\n");
    printf("- Use o camando \"5\" para enviar msg a uma sala\n");
    printf("-------------------------------------------------------------------------\n\n");
}
