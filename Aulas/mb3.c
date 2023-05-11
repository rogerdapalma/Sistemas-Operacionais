/* **************************************************************** */
/*                      Exemplo de Mailboxes                        */
/*                          INFORMAÇÕES                             */
/*                             mb3.c                                */
/* **************************************************************** */
 
#include<stdlib.h>
#include<stdio.h>
#include <sys/ipc.h>
#include <sys/msg.h>
 
int main()
{
       key_t chave;
       int filaID;
       struct msqid_ds buf;
      
       chave = ftok(".", 'B');
 
       filaID = msgget(chave, 00700);
 
       if (filaID == -1)
       {
             printf("Erro a fila de mensagens não existe\n");
             return EXIT_FAILURE;
       }
      
       msgctl(filaID, IPC_STAT, &buf);
 
       printf("\nInformações da fila %d:\n", filaID);
       printf("UID do criador: %d\n", buf.msg_perm.uid);
       printf("Permissões: %o\n", buf.msg_perm.mode);
       printf("N. de mensagens: %ld\n", buf.msg_qnum);
 
       return 0;
}
