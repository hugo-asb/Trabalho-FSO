#include <stdio.h>
#include <stdlib.h>
#include <mqueue.h>
#include <sys/stat.h>
#include <pthread.h>

#define QUEUE "/chat"

mqd_t queue;

void *receive_msg(void *msg){
  int *a = (int*)msg;
  while(1){
    if((mq_receive (queue, (void*) &a, sizeof(a), 0)) > 0){
      perror("mq_open");
      exit(1);
    }
    printf("Received msg: %d \n", *a);
    pthread_exit(0);
  }
}

int main(){
  int *msg;
  struct mq_attr attr;
  pthread_t thread_id;
  /*aguarda finalização do thread identificado por thread_id. O retorno é passado pelo ponteiro thread_res*/
  void * thread_res;

  msg = (int*)malloc(sizeof(int));

  attr.mq_maxmsg = 10;
  attr.mq_msgsize = sizeof(msg);
  attr.mq_flags = 0;

  if ((queue = mq_open (QUEUE, O_RDWR|O_CREAT, 0666, &attr)) < 0){
    perror ("mq_open");
    exit (1);
  }

  pthread_create(&thread_id, NULL, receive_msg, (void*) msg);
  pthread_join (thread_id, &thread_res);
}