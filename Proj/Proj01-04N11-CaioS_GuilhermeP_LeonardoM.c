/*
  Projeto 01, O jantar dos Filósofos - 04N11 - SO

  Nomes:
    Caio Sampaio Oliveira, TIA: 32195621;
    Guilherme Picoli Rodrigues, TIA: 32147317;
    Leonardo Henrique de Oliveira Matos, TIA: 32139561.

  Pré-requisito para a compilação:
    O programa é compatível o Sistema Operacional Linux;
    Foi utilizado as distribuições Ubuntu 20 e Ubuntu 16 para o desenvolvimento do programa.

  Como compilar:
    Para compilar o programa "Proj01-04N11-CaioS_GuilhermeP_LeonardoM.c" devemos utilizar o compilador C GCC e o seguinte comando no terminal: gcc Proj01-04N11-CaioS_GuilhermeP_LeonardoM.c -o Proj01-04N11-CaioS_GuilhermeP_LeonardoM.out

  Como executar o programa:
    Para executar o programa "Proj01-04N11-CaioS_GuilhermeP_LeonardoM.c" devemos utilizar o seguinte comando o terminal: ./Proj01-04N11-CaioS_GuilhermeP_LeonardoM.out

  Referências Bibliográficas:

    TANENBAUM, A. S. Sistemas Operacionais Modernos, 2ª Ed. São Paulo: Pearson Prentice Hall, 2005.

    VARUN. POSIX: How to create a thread | pthread_create() example & Tutorial. thisPointer, Nova Delhi, India, ago. de 2020. Disponível em: <https://thispointer.com/posix-how-to-create-a-thread-pthread_create-example-tutorial/>. Acesso em: 10 de Setembro de 2022.

    BIBI, Kalsoom. Sleep function in C. Linux Hint LLC, Sunnyvale, USA, out. de 2021. Disponível em: <https://linuxhint.com/sleep-function-c/>. Acesso em: 10 de Setembro de 2022.

*/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <stdint.h>
#include <unistd.h>
#include <time.h>

/* ----- VARIÁVEIS GLOBAIS ----- */

#define numero_threads 5

//Vetor de garfos: zero = disponível; maior que zero (ID) = reservado pelo filósofo
int quantidadeGarfos = 5, garfos[] = {0, 0, 0, 0, 0};

/* ----- FUNÇÕES AUXILIARES ----- */

// Gera um número aleatório de 1 à 5
int gerarRandomico (){

    return rand()%5;
}

/* ----- FUNÇÕES PRINCIPAIS ----- */

// Filósofo realiza a ação de pensar
void pensar(int i){

    printf("\nO filósofo %d está pensado", i+1);

    //Timer Fixo de 5 segundos
    sleep(5); //Filósofo irá pensar por 5 segundos
}

// Filósofo realiza a ação de tentar comer
void comer (int i){
    int garfosNaMao = 0; //Contabilizador de garfos na mão

    //Tenta pegar o garfo da direita
    if (garfos[i] == 0){
        garfos[i] = i; //Reserva o garfo da direita com o seu ID
        garfosNaMao = garfosNaMao + 1; //Contabiliza o nº de garfos na mão
    }

    //Verifica se é o filósofo 1
    if ((i - 1) == (-1)){
        //Tenta pegar o garfo da esquerda (que pertence ao filósofo 5)
        if (garfos[quantidadeGarfos - 1] == 0){
            garfos[quantidadeGarfos - 1] = i; //Reserva o garfo da esquerda com o seu id
            garfosNaMao = garfosNaMao + 1; //Contabiliza o nº de garfos na mão
        }
    } else {
        //Tenta pegar o garfo da esquerda (que pertence a qualquer filósofo)
        if (garfos[i - 1] == 0){
            garfos[i - 1] = i; //Reserva o garfo da esquerda com o seu ID
            garfosNaMao = garfosNaMao + 1; //Contabiliza o nº de garfos na mão
        }
    }

    //Verfica se o filósofo tem dois garfos (o da esquerda e o da direita)
    if (garfosNaMao == 2){

        printf("\nO filósofo %d está comendo", i+1);

        //Timer Fixo de 5 segundos
        sleep(5); //Filósofo irá comer por 5 segundos

        //Devolve os garfos à mesa
        for (int j = 0; j < quantidadeGarfos; j++){
            //Verifica se o garfo está reservado com o ID do filósofo
            if (garfos[j] == i){
                garfos[j] = 0; //Deixa o garfo como disponível (zero)
                garfosNaMao = garfosNaMao - 1; //Ajusta o contabilizador de garfos
            }
        }

    } else{

        //Devolve o garfo à mesa
        for (int j = 0; j < quantidadeGarfos; j++){
            //Verifica se o garfo está reservado com o ID do filósofo
            if (garfos[j] == i){
                garfos[j] = 0; //Deixa o garfo como disponível (zero)
                garfosNaMao = garfosNaMao - 1; //Ajusta o contabilizador de garfos
            }
        }
    }
}

// Define as ações de cada filósofo na mesa
void *acoesNaMesa(void *arg){
    int i = (intptr_t)arg;
    
    //Cada filósofo executa as ações de pensar e comer indefinidamente
    for (;;){
        pensar(i); //Primeiro o filósofo pensa
        comer(i); //Segundo ele tenta comer
    }
}

/* ----- MAIN ----- */

// Programa Principal
int main(){

    int status;
    pthread_t filosofos[numero_threads];

    //Cria os filósofos com threads
    for(int i = 0; i < numero_threads; i++){

        //Cria cada filósofo executando o método acoesNaMesa e salva o status de criação
        status = pthread_create(&filosofos[i], NULL, acoesNaMesa, (void*)(intptr_t)i);

        //Verifica se a criação foi bem-sucedida
        if(status != 0){
            printf("O filsofo recusou-se a sentar na mesa %d\n", status);
        } else{
            printf("O filsofo %d sentou-se a mesa\n", i);
        }
    }

    //Espera cada thread (filósofo) terminar
    for(int i = 0; i < numero_threads; i++){
	
	//Realiza o join de cada filósofo e salva o status da operação
        status = pthread_join(filosofos[i], NULL);
        
        //Verifica se a operação foi bem-sucedida
        if(status != 0){
            printf("O filsofo morreu à mesa %d\n", status);
        }
    }

    return 0;
}
