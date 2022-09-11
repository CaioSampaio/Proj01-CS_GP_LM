/*
  Projeto 01, O jantar dos Filósofos - 04N11 - SO
  
  Nomes:
   Caio Sampaio Oliveira, TIA:32195621;
   Guilherme Picoli Rodrigues, TIA:32147317;
   Leonardo Henrique de Oliveira Matos, TIA:32139561.
   
  Pré-requisito para a compilação:
   O programa é compatível o Sistema Operacional Linux;
   Foi utilizado as distribuições Ubuntu 20 e Ubuntu 16 para o desenvolvimento do programa.
   
  Como compilar:
   Para compilar o programa "Proj01-04N11-CaioS_GuilhermeP_LeonardoM.c" devemos utilizar o compilador C GCC e o seguinte comando no terminal: gcc Proj01-04N11-CaioS_GuilhermeP_LeonardoM.c -o Proj01-04N11-CaioS_GuilhermeP_LeonardoM.out
   
  Como executar o programa:
   Para executar o programa "Proj01-04N11-CaioS_GuilhermeP_LeonardoM.c" devemos utilizar o seguinte comando o terminal: ./Proj01-04N11-CaioS_GuilhermeP_LeonardoM.out 

  Referências Bibliográficas:
  
   TANENBAUM, A. S. Sistemas Operacionais Modernos, 2ª Ed. São Paulo: Pearson Prentice Hall, 2005.
   
   VARUN. POSIX: How to create a thread | pthread_create() example & Tutorial. thisPointer, Nova Delhi, India, ago. de 2020. Disponível em: https://thispointer.com/posix-how-to-create-a-thread-pthread_create-example-tutorial/. Acesso em: 10 de Setembro de 2022.

*/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <stdint.h>
#include <unistd.h>
#include <time.h>

#define numero_threads 5

int quantidadeGarfos = 5, garfos[] = {0, 0, 0, 0, 0};

int gerarRandomico (){

  return rand()%5;
}

void pensar(int i){

  printf("\nO filósofo %d está pensado", i+1);
  //Timer Randômico
  sleep(gerarRandomico());
}

void comer (int i){
  int garfosNaMao = 0;

  /*for (int j = 0; j < quantidadeGarfos; j++){
    if (garfos[j] == 0){
      garfos[j] = i;
      garfosNaMao = garfosNaMao + 1;
    }
  }*/
  
  if (garfos[i] == 0){
      garfos[i] = i;
      garfosNaMao = garfosNaMao + 1;
  }
  
  if ((i - 1) == (-1)){
      if (garfos[quantidadeGarfos - 1] == 0){
        garfos[quantidadeGarfos - 1] = i;
        garfosNaMao = garfosNaMao + 1;
      }
  } else {
      if (garfos[i - 1] == 0){
        garfos[i - 1] = i;
        garfosNaMao = garfosNaMao + 1;
      }
  }

  if (garfosNaMao == 2){

    printf("\nO filósofo %d está comendo", i+1);

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

int main(){

  int status;
  pthread_t filosofos[numero_threads];

  for(int i = 0; i < numero_threads; i++){

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

  return 0;
}
