#include <stdio.h>
#include <stdlib.h>
#include <mqueue.h>
#include <sys/stat.h>
#include <pthread.h>
#include "constants.h"
#include "chat.h"


/* TODO: Fazer o usuario digitar o nome da fila que ele esta criando 
  Para fins de teste foi criado o arquivo teste.c, que cria a fila /chat2,
  para o qual esse programa esta mandando a msg */

void *send_msg(){
  int msg;

  // Mudar /chat2 pra fila para qual a msg sera enviada
  if ((q_send = mq_open ("/chat2", O_RDWR)) < 0){
    perror ("mq_open");
    exit (1);
  }

  while(1){

    printf("Digite a msg: " );
    scanf("%d", &msg);

    if((mq_send (q_send, (void*) &msg, sizeof(msg), 0)) < 0){
      perror("mq_send");
      exit(1);
    }
    printf("Send msg: %d \n", msg);
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
  }
}

