#include <stdio.h>
#include <pthread.h>
#include <time.h>
#include <stdlib.h>

/*
 * quantidade de números que serão produzidos/consumidos.
 */
#define MAX_NUMBERS 10
/*
 * tamanho do buffer compartilhado.
 */
#define BUFFER_MAX 4
/*
 * mutex para controlar o acesso a região crítica (buffer, empty e full).
 */
pthread_mutex_t mutex_rc = PTHREAD_MUTEX_INITIALIZER;
/*
 * condição para sinalização do consumidor (avisa que pode consumir).
 */
pthread_cond_t cond_consumer = PTHREAD_COND_INITIALIZER;
/*
 * condição para sinalização do produtor (avisa que pode produzir).
 */
pthread_cond_t cond_producer = PTHREAD_COND_INITIALIZER;

// início da região crítica **************************************

/*
 * buffer compartilhado entre o produtor e o consumidor.
 */
int buffer[BUFFER_MAX];
/*
 * variável que conta quantos empaços do buffer estão vazios.
 */
int empty = BUFFER_MAX;
/*
 * variável que conta quantos espaços do buffer estão cheios.
 */
int full = 0;

// fim da região crítica *****************************************

/*
 * rotina de execução do produtor.
 */
void *producer_routine()
{
    for (int c = 0; c < MAX_NUMBERS;)
    {
        // trava a mutex para poder manipular a região crítica.
        pthread_mutex_lock(&mutex_rc);
        // se não houver espaço vazio para produzir no buffer, a thread espera por um sinal para acordar
        while (full == BUFFER_MAX)
        {
            pthread_cond_wait(&cond_producer, &mutex_rc);
        }
        int pos = 0;
        /*
        * gera todos os números que cabem no buffer,
        * sempre verificando se a quantidade total foi atingida.
        */
        for (int i = empty; i > 0 && c < MAX_NUMBERS;)
        {
            int item = rand() % 100 + 1;
            buffer[pos] = item;
            full++;
            empty--;
            c++;
            i--;
            // segurança para index em "lista circular".
            pos = (pos + 1) % BUFFER_MAX;
        }
        // acorda o consumidor e sai da região crítica.
        pthread_cond_signal(&cond_consumer);
        pthread_mutex_unlock(&mutex_rc);
    }
    // fecha a thread.
    pthread_exit(0);
}

/*
 * rotina de execução do consumidor.
 */
void *consumer_routine()
{
    for (int c = 0; c < MAX_NUMBERS;)
    {
        // trava a mutex para poder manipular a região crítica.
        pthread_mutex_lock(&mutex_rc);
        // se não existir números para consumir, a thread espera por um sinal para acordar.
        while (empty == BUFFER_MAX)
        {
            pthread_cond_wait(&cond_consumer, &mutex_rc);
        }
        int pos = 0;
        /*
        * lê todos os números disponíveis no buffer, 
        * sempre verificando a quantidade de números a serem lidos no total.
        * Após ler o valor, o exibe no terminal.
        */
        for (int i = full; i > 0 && c < MAX_NUMBERS;)
        {
            int item = buffer[pos];
            full--;
            empty++;
            c++;
            i--;
            // segurança para index em "lista circular".
            pos = (pos + 1) % BUFFER_MAX;
            printf("%d ", item);
        }
        printf("\n");
        // acorda o produtor e sai da região crítica.
        pthread_cond_signal(&cond_producer);
        pthread_mutex_unlock(&mutex_rc);
    }
    // fecha a thread.
    pthread_exit(0);
}

int main(int argc, char const *argv[])
{
    // seed para geração de números aleatórios.
    srand(time(NULL));
    // as threads do produtor e consumidor.
    pthread_t producer, consumer;
    // cria as duas threads.
    pthread_create(&consumer, 0, consumer_routine, 0);
    pthread_create(&producer, 0, producer_routine, 0);
    // espera a finalização das duas threads.
    pthread_join(producer, 0);
    pthread_join(consumer, 0);
    // destroy as condições e o mutex.
    pthread_cond_destroy(&cond_consumer);
    pthread_cond_destroy(&cond_producer);
    pthread_mutex_destroy(&mutex_rc);
    return 0;
}
