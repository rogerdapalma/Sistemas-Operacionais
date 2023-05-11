#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>

#define N 1000000

int num = 0;
sem_t semaforo;

void* contaIteracoes(void* nome){
	int aux, i, valorSem;

	
	for(i=0;i<N;i++){
		sem_wait(&semaforo);
		aux = num;
		aux = aux + 1;
		num = aux;
		sem_post(&semaforo);		
	}
	sem_getvalue(&semaforo, &valorSem);
	printf("O valor do semáforo eh %d\n", valorSem);

	pthread_exit(0);
}

int main(){
	int i;
	pthread_t thUm, thDois;

	sem_init(&semaforo, 0, 1);
	pthread_create(&thUm, 0, contaIteracoes, "Um");
	pthread_create(&thDois, 0, contaIteracoes, "Dois");
	
	pthread_join(thUm, NULL);
	pthread_join(thDois, NULL);

	if(num != 2*N)
		printf("**** ERRO na SOMA TOTAL das iteracoees dos Threads ****\nnum = %d\n", num);
	else
		printf("OK! SOMA FINAL CORRETA!!!\nnum = 2 * N = %d\n", num);
	sem_destroy(&semaforo);
	printf("Fim do Thread Principal\n");

	return 1;
}

