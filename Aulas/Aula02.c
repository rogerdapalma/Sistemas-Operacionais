/*
   Exemplo de manipulação de threads extraído e adaptado do Livro Aberto
   de Sistemas Operacionais, de Carlos Maziero.
*/

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h> //para usar a função exit
#include <unistd.h> //para usar a função sleep 

#define NUM_THREADS 5

void *print_hello (void *threadid)
{
	printf ("%ld: Hello World!\n", (long) threadid);
	sleep (5) ;
	printf ("%ld: Bye bye World!\n", (long) threadid);
	pthread_exit (NULL); // encerra esta thread
}

// thread "main"
int main (int argc, char *argv[])
{
	pthread_t thread[NUM_THREADS];
	long status, i;

	// cria as demais threads
	for(i = 0; i < NUM_THREADS; i++)
	{
		printf ("Creating thread %ld\n", i);
		status = pthread_create (&thread[i], NULL, print_hello, (void *) i);

		if (status) // ocorreu um erro na criação
		{
			perror ("pthread_create");
			exit (-1);
		}
	}

	// encerra a thread "main"
	pthread_exit (NULL);
}

