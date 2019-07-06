#ifndef CHANNEL_H_
#define CHANNEL_H_
void create_channel(char* channel_name);
void add_to_channel(char * name);
void remove_channel(char * name);
void * send_msg_channel(char * from, char * msg);
void * channel_receive();
char * format_channel_name();
#endif
