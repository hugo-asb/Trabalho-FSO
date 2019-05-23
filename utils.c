#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
