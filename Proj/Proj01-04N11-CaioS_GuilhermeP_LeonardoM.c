#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <stdint.h>

#define numero_threads 5

int quantidadeGarfos, garfos[] = {0, 0, 0, 0, 0};

void pensar(int i){
  printf("\nO filósofo %d está pensado", i);
  //Timer Randômico
}

void comer (int i){
  int garfosNaMao = 0;

  for (int j = 0; j < quantidadeGarfos; j++){
    if (garfos[j] == 0){
      garfos[j] = i;
      garfosNaMao = garfosNaMao + 1;
    }
  }

  if (garfosNaMao == 2){

    printf("\nO filósofo %d está comendo", i);

    //Timer Randômico

    for (int j = 0; j < quantidadeGarfos; j++){
      if (garfos[j] == i){
        garfos[j] = 0;
        garfosNaMao = garfosNaMao - 1;
      }
    }

  } else{
     for (int j = 0; j < quantidadeGarfos; j++){
      if (garfos[j] == i){
        garfos[j] = 0;
        garfosNaMao = garfosNaMao - 1;
      }
    }
  }
}

void *acoesNaMesa(void *arg){
  int i = (int)arg;

  for (;;){
    pensar(i);
    comer(i);
  }
}

/*
void *imprimirFilosofo(void* tid){

  printf("O filósifo %p\n", tid);
  pthread_exit(NULL);
}
*/

int main(){

  int status;
  pthread_t filosofos[numero_threads];

  for(int i = 0; i < numero_threads; i++){

    printf("Main here. Creating thread %d\n", i);
    //status = pthread_create(&filosofos[i], NULL, imprimirFilosofo,(void*)(intptr_t)i);
    status = pthread_create(&filosofos[i], NULL, acoesNaMesa, (void*)(intptr_t)i);

    if(status != 0){
      printf("Erro ao criar o filsofo %d\n", status);
    }
  }

  return 0;
}
