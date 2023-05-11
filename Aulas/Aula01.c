/* 
   Exemplo de criação de threads com POSIX threads.
   Este exemplo cria duas threads que executarão concorrentemente a função mostraCidade
*/
#include <pthread.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h> 

//A função a seguir é executada por cada uma das threads
//Na biblioteca pthread, sempre a função que será executada pelas threads deve retornar void* e sempre tem um argumento void*,
//ou seja, ponteiro para void (ponteiro genérico). Se precisarmos passar mais de um dado para a thread, devemos usar os tipos
// compostos em C, como por exemplo, struct.
void* mostraCidade(void* nome)
{
       int aux1, aux2, aux3, count;
 
       if (strcmp(nome, "Santa Maria") == 0) //Se o nome da thread for "Santa Maria" count = 50
             count = 50;
       else //se não, count = 100. Esta variável é usada para mudar a quantidade de iterações por thread
             count = 100;
 
       for(aux1=0; aux1<count; aux1++)
       {
             printf("%d %s\n", aux1, (char *) nome);
             /* Cria uma espera, sem suspender a thread */
             for(aux2=rand()/10000;aux2>0;aux2--)
               for(aux3=10;aux3>0;aux3--);
       }
       pthread_exit(0); //finaliza a thread
}
// a função principal main(), equivale à execução da thread principal do programa.
//Com a função pthread_create, criamos as outras threads
int main()
{
       int i;
       pthread_t thUm, thDois; //observe que é necessário declarar uma variável do tipo thread pthread_t, para cada thread a ser criada.


       //São criadas e disparadas (iniciada a execução) de duas threads com a função pthread_create.
       //O primeiro argumento da função tem o endereço da variável do tipo pthread_t
       //O segunda argumento da função tendo 0 ou NULL, significa que todos os atributos da thread são criados com valores default
       //O terceiro argumento é a função que a thread irá executar
       //O quarto argumento é o que será passado para a função que a thread irá executar, neste caso o nome.
       pthread_create(&thUm, 0, mostraCidade, "Santa Maria");
       pthread_create(&thDois, 0, mostraCidade, "Porto Alegre");

       //A thread principal espera as threads criadas. O primeiro argumento de pthread_join é a variável que identifica a thread
       // e o segundo, como o retorno é nulo, é zero, pois não precisa armazenar o retorno da thread      
       pthread_join(thUm, 0);
       pthread_join(thDois, 0);
 
       printf("Fim do Thread Principal\n");
       return 0;
}

