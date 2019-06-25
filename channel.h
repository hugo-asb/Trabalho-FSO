#ifndef
    void create_channel(char* channel_name);
    void add_to_channel(char * name);
    void remove();
    void * send_msg_channel(char * from, char * msg);
    void * channel_receive();
#endif
