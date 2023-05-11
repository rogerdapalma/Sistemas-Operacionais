#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#define N 100000000
int num = 0;

void* contaIteracoes(void* nome){
	int aux, i;

	//id = atoi(nome);
        printf("Thread %s\n", (char *)nome);

	for(i=0;i<N;i++)	{
		aux = num;
		aux = aux + 1;
		num = aux;
		
	}

	pthread_exit(0);
}

int main(){
	int i;
	pthread_t thUm, thDois;

	pthread_create(&thUm, 0, contaIteracoes, "Um");
	pthread_create(&thDois, 0, contaIteracoes, "Dois");
	
	pthread_join(thUm, NULL);
	pthread_join(thDois, NULL);

	if(num != 2*N)
		printf("**** ERRO na SOMA TOTAL das iteracoees dos Threads ****\nnum = %d\n", num);
	else
		printf("OK! SOMA FINAL CORRETA!!!\nnum = 2 * N = %d\n", num);
	printf("Fim do Thread Principal\n");
	return 1;
}

