# Projeto 01, O jantar dos Filósofos:

## O Grupo:

* Caio Sampaio Oliveira, TIA 32195621;
* Guilherme Picoli Rodrigues, TIA 32147317;
* Leonardo Henrique de Oliveira Matos, TIA 32139561.

## O Programa:

### Pré-requisito para a compilação:

  O programa é compatível o Sistema Operacional Linux;
Foi utilizado as distribuições Ubuntu 20 e Ubuntu 16 para o desenvolvimento do programa.

### Como compilar o programa:

  Para compilar o programa "Proj01-04N11-CaioS_GuilhermeP_LeonardoM.c" devemos utilizar o compilador C GCC e o seguinte comando no terminal:
gcc Proj01-04N11-CaioS_GuilhermeP_LeonardoM.c -o Proj01-04N11-CaioS_GuilhermeP_LeonardoM.out

### Como executar o programa:

  Para executar o programa "Proj01-04N11-CaioS_GuilhermeP_LeonardoM.c" devemos utilizar o seguinte comando o terminal:
./Proj01-04N11-CaioS_GuilhermeP_LeonardoM.out

### Como comprovar que os resultados propostos foram alcançados:

  O programa deve imprimir na tela o que cada filósofo está fazendo no momento, seja comendo ou pensando, de modo que
cada filósofo deve ter a sua vez de comer e quando não for possível comer, o mesmo deve estar pensando. Assim, essa
alternância não deve resultar em starvation.

### Funcionamento do programa:

  Inicialmente, o programa cria cada filósofo como uma thread. A cada criação de filósofo (thread) é executado o método _acoesNaMesa()_ com o ID de cada filósofo e,
consequentemente, cada filósofo iniciará suas rotinas de ações na mesa, pensar e comer, continuamente.
  Assim, o método _acoesNaMesa()_ irá, primeiramente, para um determinado filósofo, chamar o método _pensar()_. Este método é responsável por imprimir que o filósofo, identificado por seu ID, está pensando e em seguida o método coloca-o, por meio do _sleep()_, para pensar por tempo fixo de cinco segundos. Todos os filósofos são colocados para pensar imediatamente após sentarem à mesa, isto é, ao serem criados.
  Consecutivamente, o método _acoesNaMesa()_ irá chamar o método _comer()_. O método é incumbido de tentar fazer o filósofo comer: primeiro tenta-se reservar o garfo da direita e caso seja possível, um contabilizador da quantidade de garfos na mão (reservados) do filósofo é incrementado; depois, tenta-se reservar o garfo da esquerda e caso seja possível, novamente o contabilizador é incrementado; por fim, verifica-se, por intermédio do contabilizador, se o filósofo possuí os dois garfos, comendo (print indicando a ação) por cinco segundos em caso afirmativo, e devolvendo os garfos em seguida, ou apenas devolvendo os garfos em caso negativo.
  Os garfos são dispostos em um vetor de inteiros de valores zeros, com a ação de reservar o garfo ocorrendo quando no lugar do zero, coloca-se o ID do filósofo. Isso só ocorre quando o garfo não possui um ID, ou seja, está com o valor como zero. Outro limitante decorre do fato do filósofo só poder reservar o garfo da esquerda e o da direita. Deste modo, esse vetor funciona com base no princípio de semáforo, sendo, junto a criação dos filósofos como thread, parte crucial para a solução do problema da Comunicação Inter Processos (IPC).
