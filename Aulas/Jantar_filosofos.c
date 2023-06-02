#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

#define NUM_FILOSOFOS 5
#define ESQUERDA(id) (id)
#define DIREITA(id) (((id) + 1) % NUM_FILOSOFOS)

sem_t garfos[NUM_FILOSOFOS];
sem_t mutex;

void pensar(int id) {
    printf("Filósofo %d está pensando.\n", id);
}

void pegarGarfos(int id) {
    sem_wait(&mutex);
    sem_wait(&garfos[ESQUERDA(id)]);
    sem_wait(&garfos[DIREITA(id)]);
    sem_post(&mutex);
    printf("Filósofo %d pegou os garfos.\n", id);
}

void comer(int id) {
    printf("Filósofo %d está comendo.\n", id);
    sleep(2); // Simula o tempo que o filósofo leva para comer
}

void largarGarfos(int id) {
    sem_post(&garfos[ESQUERDA(id)]);
    sem_post(&garfos[DIREITA(id)]);
    printf("Filósofo %d largou os garfos.\n", id);
}

void *filosofo(void *arg) {
    int id = *(int *)arg;
    int count = 0;

    while (count < 3) { // Filósofos comem 3 vezes
        pensar(id);
        pegarGarfos(id);
        comer(id);
        largarGarfos(id);
        count++;
    }

    return NULL;
}

int main() {
    pthread_t filosofos[NUM_FILOSOFOS];
    int ids[NUM_FILOSOFOS];

    // Inicializa os semáforos
    for (int i = 0; i < NUM_FILOSOFOS; i++)
        sem_init(&garfos[i], 0, 1);
    sem_init(&mutex, 0, 1);

    // Cria as threads dos filósofos
    for (int i = 0; i < NUM_FILOSOFOS; i++) {
        ids[i] = i;
        pthread_create(&filosofos[i], NULL, filosofo, &ids[i]);
    }

    // Aguarda a finalização das threads
    for (int i = 0; i < NUM_FILOSOFOS; i++)
        pthread_join(filosofos[i], NULL);

    // Libera os semáforos
    for (int i = 0; i < NUM_FILOSOFOS; i++)
        sem_destroy(&garfos[i]);
    sem_destroy(&mutex);

    return 0;
}
