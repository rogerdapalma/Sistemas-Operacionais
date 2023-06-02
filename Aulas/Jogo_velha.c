#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define NUM_THREADS 2
#define NUM_ROUNDS 10 

int placar[NUM_THREADS] = {0};
pthread_mutex_t mutex;

void *jogar(void *thread_id) {
    int id = *(int *)thread_id;
    int i;
    
    for (i = 0; i < NUM_ROUNDS; i++) {
        pthread_mutex_lock(&mutex); // Bloqueia o acesso para a outra thread
        
        // Simula o lançamento de um dado (gera um número aleatório entre 1 e 6)
        int resultado = rand() % 6 + 1;
        
        printf("Jogador %d lançou o dado e obteve: %d\n", id, resultado);
        
        placar[id] += resultado;
        
        printf("Placar parcial da rodada %d: Jogador 1 - %d, Jogador 2 - %d\n", i+1, placar[0], placar[1]);
        
        pthread_mutex_unlock(&mutex); // Libera o acesso para a outra thread
        
        // Espera um tempo antes da próxima rodada
        sleep(1);
    }
    
    pthread_exit(NULL);
}

int main() {
    int i;
    pthread_t threads[NUM_THREADS];
    int thread_ids[NUM_THREADS] = {0, 1};
    
    pthread_mutex_init(&mutex, NULL); // Inicializa o mutex
    
    // Cria as threads
    for (i = 0; i < NUM_THREADS; i++) {
        pthread_create(&threads[i], NULL, jogar, (void *)&thread_ids[i]);
    }
    
    // Aguarda as threads terminarem
    for (i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }
    
    // Exibe o placar final
    printf("\nPlacar Final: Jogador 1 - %d, Jogador 2 - %d\n", placar[0], placar[1]);
    
    pthread_mutex_destroy(&mutex); // Destroi o mutex
    
    return 0;
}
