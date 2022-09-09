
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define numero_threads 2

void *imprimirFilosofo(void *tid){
  
  printf("O filósifo %d\n", tid);
  pthred_exit(NULL);
}

int main(){
  
  int status;
  pthreads_t filosofos[numero_threads]
  
  for(int i = 0, i < numero_threads; i++){
    
    print("Main here. Creating thread %d\n", i);
    status = pthread_creat(&filosofos[i], NULL, imprimirFilosofo, (void*)i);
    
    if(status != 0){
      printf("Erro ao criar o filsofo %d\n", status);
    }
  }
  
  return 0;
}

