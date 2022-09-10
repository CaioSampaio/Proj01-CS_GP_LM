
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define numero_threads 2

/*

int quantidadeGarfos, garfos[] = {0, 0, 0, 0, 0};

void pensar(int i){
  printf("O filósofo %d está pensado", i);
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
  
    printf("O filósofo %d está comendo", i);
  
    //Timer Randômico
    
    for (int j = 0; j < quantidadeGarfos; j++){
      if (garfos[j] == i){
        garfos[j] = 0;
        garfosNaMao = garfosNaMao - 1;
      }
    }
    
  }
}

void *acoesNaMesa(void *tid, int i){
  
  for (;;){
    pensar();
    comer();
  }
}

*/

void *imprimirFilosofo(void *tid){
  
  printf("O filósifo %d\n", tid);
  pthred_exit(NULL);
}

int main(){
  
  int status;
  pthreads_t filosofos[numero_threads];
  
  for(int i = 0, i < numero_threads; i++){
    
    print("Main here. Creating thread %d\n", i);
    status = pthread_creat(&filosofos[i], NULL, imprimirFilosofo, (void*)i);
    // status = pthread_creat(&filosofos[i], NULL, acoesNaMesa, (void*)i);
    
    if(status != 0){
      printf("Erro ao criar o filsofo %d\n", status);
    }
  }
  
  return 0;
}

