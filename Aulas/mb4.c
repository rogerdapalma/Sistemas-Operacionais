/* **************************************************************** */
/*                      Exemplo de Mailboxes                        */
/*                        REMOVER MAILBOX                           */
/*                             mb4.c                                */
/* **************************************************************** */
 
#include<stdlib.h>
#include<stdio.h>
#include <sys/ipc.h>
#include <sys/msg.h>
 
int main()
{
       key_t chave;
       int filaID;
      
       chave = ftok(".", 'B');
 
       filaID = msgget(chave, 00700);
 
       if (filaID == -1)
       {
             printf("Erro a fila de mensagens não existe\n");
             return EXIT_FAILURE;
       }
      
       if (!msgctl(filaID, IPC_RMID, NULL))
             printf("Caixa de Mensagem removida com sucesso\n");
       else
       {
             printf("Erro na remoção...\n");
              exit(-1);
       }
 
       return 0;
}
