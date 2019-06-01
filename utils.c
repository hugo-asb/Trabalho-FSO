#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void list(){
    
    DIR * dir;
    struct dirent *folder;
    dir = opendir("/dev/mqueue/");
    char * buffer = ".";
    char * buffer2 = "..";
    if(dir){
        printf("Pessoas Online\n")
        while((folder = readdir(dir))!=NULL){
            if(strcmp(folder->d_name, buffer)!=0 && strcmp(folder->d_name, buffer2)!=0){
            char *name = folder->d_name;
            name +=5;
            printf("%s\n", name);       
            }
        }
    }
}

char * name_chat_format(char * name){

    char * delimiter = (char*)malloc(sizeof(char)*20);
    strcat(delimiter, "/chat-");
    char * queue_name = name;
    strcat(delimiter, name);
    
    return delimiter;

}
