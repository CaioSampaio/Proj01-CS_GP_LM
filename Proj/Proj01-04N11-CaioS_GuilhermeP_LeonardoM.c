#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <stdint.h>
#include <unistd.h>
#include <time.h>

#define numero_threads 5

int quantidadeGarfos = 2, garfos[] = {0, 0, 0, 0, 0};

int gerarRandomico (){

  return rand()%5;
}

void pensar(int i){

  printf("\nO filósofo %d está pensado", i);
  //Timer Randômico
  sleep(gerarRandomico());
}

void comer (int i){
  int garfosNaMao = 0;

  for (int j = 0; j < quantidadeGarfos; j++){
    if (garfos[j] == 0){
      garfos[j] = i;
      garfosNaMao = garfosNaMao + 1;
    }
  }

  printf("\nO filósofo %d tem %d garfos", i, garfosNaMao);

  if (garfosNaMao == 2){

    printf("\nO filósofo %d está comendo", i);

    //Timer Randômico
    sleep(gerarRandomico());

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
  int i = (intptr_t)arg;

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

    //status = pthread_create(&filosofos[i], NULL, imprimirFilosofo,(void*)(intptr_t)i);
    status = pthread_create(&filosofos[i], NULL, acoesNaMesa, (void*)(intptr_t)i);

    if(status != 0){
        printf("O filsofo recusou-se a sentar na mesa %d\n", status);
    } else{
        printf("O filsofo %d sentou-se a mesa\n", i);
    }
  }

  for(int i = 0; i < numero_threads; i++){

    status = pthread_join(filosofos[i], NULL);

    if(status != 0){
      printf("O filsofo morreu à mesa %d\n", status);
    }
  }

  //for(int i = 0; i < numero_threads; i++){

    //acoesNaMesa(void *arg);
  //}

  return 0;
}
