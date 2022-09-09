#include <stdio.h>
#include <stdlib.h>
#include <pthreads.h>

#define NUMBER_OF_THREADS 2

void *print_hello_world(void *tid){
  
  printf("Hello World. Greetings from threads %d\n", tid);
  pthred_exit(NULL);
}

int main(){
  
  pthreads_t threads[NUMBER_OF_THREADS]
  int status, i;
  
  for(i=0, i<NUMBER_OF_THREADS; i++){
    
    print("Main here. Creating thread %d\n", i);
    status = pthread_creat(&threads[i], NULL, print_hello_world, (void*)i);
    
    if(status != 0){
      printf("Ops. pthread_creat returned error code %d\n", status)
      }
  }
  
  return 0;
}

