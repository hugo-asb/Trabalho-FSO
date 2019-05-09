#include <stdio.h>
#include <stdlib.h>
#include <mqueue.h>
#include <sys/stat.h>
#include <pthread.h>

#define QUEUE "/chat"

mqd_t queue;

void *send_msg(){
  int msg;

  while(1){
    msg = rand() % 100;

    if((mq_send (queue, (void*) &msg, sizeof(msg), 0)) < 0){
      perror("mq_send");
      exit(1);
    }
    printf("Send msg: %d \n", msg);
  }
}

int main(){
  pthread_t thread_id;
  /*aguarda finalização do thread identificado por thread_id. O retorno é passado pelo ponteiro thread_res*/
  void * thread_res;

  if ((queue = mq_open (QUEUE, O_RDWR)) < 0){
    perror ("mq_open");
    exit (1);
  }

  pthread_create(&thread_id, NULL, send_msg, NULL);
  pthread_join (thread_id, &thread_res);
}