#ifndef CHAT_H_
#define CHAT_H_
void * send_msg(char* from, char* by, char *msg);
void * receive_msg(void *msg);
void * handler_msg();
void * broadcast(char* from, char*msg);
#endif
