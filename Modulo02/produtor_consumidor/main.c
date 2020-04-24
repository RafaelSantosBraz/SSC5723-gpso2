#include <stdio.h>
#include <pthread.h>
#include <time.h>
#include <stdlib.h>

#define MAX_NUMBERS 10
#define BUFFER_MAX 4

pthread_mutex_t mutex_rc = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond_consumer = PTHREAD_COND_INITIALIZER;
pthread_cond_t cond_producer = PTHREAD_COND_INITIALIZER;

int buffer[BUFFER_MAX];
int empty = BUFFER_MAX;
int full = 0;

pthread_t producer;
pthread_t consumer;

void *producer_routine()
{
    for (int c = 0; c < MAX_NUMBERS;)
    {
        pthread_mutex_lock(&mutex_rc);
        while (full == BUFFER_MAX)
        {
            pthread_cond_wait(&cond_producer, &mutex_rc);
        }
        int pos = 0;
        for (int i = empty; i > 0 && c < MAX_NUMBERS;)
        {
            int item = rand() % 100 + 1;
            buffer[pos] = item;
            full++;
            empty--;
            c++;
            i--;
            pos = (pos + 1) % BUFFER_MAX;
        }
        pthread_cond_signal(&cond_consumer);
        pthread_mutex_unlock(&mutex_rc);
    }
    pthread_exit(0);
}

void *consumer_routine()
{
    for (int c = 0; c < MAX_NUMBERS;)
    {
        pthread_mutex_lock(&mutex_rc);
        while (empty == BUFFER_MAX)
        {
            pthread_cond_wait(&cond_consumer, &mutex_rc);
        }
        int pos = 0;
        for (int i = full; i > 0 && c < MAX_NUMBERS;)
        {
            int item = buffer[pos];
            full--;
            empty++;
            c++;
            i--;
            pos = (pos + 1) % BUFFER_MAX;
            printf("%d ", item);
        }
        printf("\n");
        pthread_cond_signal(&cond_producer);
        pthread_mutex_unlock(&mutex_rc);
    }
    pthread_exit(0);
}

int main(int argc, char const *argv[])
{
    srand(time(NULL));

    pthread_create(&consumer, 0, consumer_routine, 0);
    pthread_create(&producer, 0, producer_routine, 0);
    pthread_join(producer, 0);
    pthread_join(consumer, 0);

    pthread_cond_destroy(&cond_consumer);
    pthread_cond_destroy(&cond_producer);
    pthread_mutex_destroy(&mutex_rc);
    return 0;
}
