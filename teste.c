#include <stdio.h>
#include <stdlib.h>
#include <mqueue.h>
#include <sys/stat.h>
#include <pthread.h>

#define QUEUE "/chat2"

// Esse Programa manda a msg para chat.c

mqd_t q_send, q_receive;

void *send_msg(){
  int msg;

  if ((q_send = mq_open ("/chat", O_RDWR)) < 0){
    perror ("mq_open");
    exit (1);
  }

  while(1){
    // msg = rand() % 10;
    printf("Digite a msg :" );
    scanf("%d", &msg);

    if((mq_send (q_send, (void*) &msg, sizeof(msg), 0)) < 0){
      perror("mq_send");
      exit(1);
    }
    printf("Send msg2: %d \n", msg);
  }
}

void *receive_msg(void *msg){
  int *msg_received = (int*)msg;

  while(1){
    if((mq_receive (q_receive, (void*) &msg_received, sizeof(msg_received), 0)) < 0){
      perror("mq_open");
      exit(1);
    }

    printf("Received msg: %d \n", msg_received);
    //pthread_exit(0);
  }
}

int main(){
  int *msg;
  struct mq_attr attr;
  pthread_t receive, send;
  /*aguarda finalização do thread identificado por thread_id. O retorno é passado pelo ponteiro thread_res*/
  void * thread_res;

  msg = (int*)malloc(sizeof(int));

  attr.mq_maxmsg = 10;
  attr.mq_msgsize = sizeof(msg);
  attr.mq_flags = 0;

  if ((q_receive = mq_open (QUEUE, O_RDWR|O_CREAT, 0666, &attr)) < 0){
    perror ("mq_open");
    exit (1);
  }

  pthread_create(&send, NULL, send_msg, NULL);
  pthread_create(&receive, NULL, receive_msg, (void*) msg);
  pthread_join (receive, &thread_res);
}