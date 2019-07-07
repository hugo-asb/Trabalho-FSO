#ifndef CONSTANTS_H_
#define CONSTANTS_H_

#include <mqueue.h>
#include <sys/stat.h>
#include "types.h"
mqd_t q_send, q_receive, q_receive_channel, q_send_channel;
char * queue_name;
char * channel;
int has_channel;
User_channel users[50];
int count_;
#endif
