#include <stdlib.h>
#include <stdio.h>
#include "types.h"

char * read_message(){
    
    char * content = (char*)malloc(sizeof(char)*522);
    int i = 0;
    char c;
    do{
       c = getchar();
       content[i] = c;
       i++;
    }while(c!='\n');
    return content;
}

char * find(char * content, int *pos){
    int i = *pos;
    char c;
    int k = 0;
    int j = *pos;
    do{
        
        c = content[*pos];
        i++;
        *pos = i;

    }while(c!=':' && c!='\n');
    
    char * element =(char*)malloc(sizeof(char)*i-j);
    
    while(j!=i-1){
        element[k] = content[j];
        j++;
        k++;
    }
    return element;
}

Msg * get_attrs_msg(char * content){
    int pos = 0;
    Msg *msg = (Msg*)malloc(sizeof(Msg));
    msg->sender = (char*)malloc(sizeof(char)*10);
    msg->receive = (char*)malloc(sizeof(char)*10);
    msg->content =(char*)malloc(sizeof(char)*500);
    msg->sender = find(content, &pos);
    msg->receive = find(content, &pos);
    msg->content = find(content, &pos);
    return msg;
}
