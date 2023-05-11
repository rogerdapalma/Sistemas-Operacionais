/* **************************************************************** */
/*                      Exemplo de Mailboxes                        */
/*                       ENVIO DE MENSAGENS                         */
/*                             mb1.c                                */
/* **************************************************************** */
 
#include<stdlib.h>
#include<string.h>
#include<stdio.h>
#include <sys/ipc.h>
#include <sys/msg.h>
 
struct mensagem{
       long tipo;
       char texto[256];
};
 
int main()
{
       key_t chave;
       int filaID, i=0;
       struct mensagem msg;
       char buffer[256];
       struct msqid_ds fila;
 
       chave = ftok(".", 'B');
 
       filaID = msgget(chave, IPC_CREAT | 00700);
       if (filaID == -1)
       {
             printf("Erro na criação da fila de mensagens\n");
             return -1;
       }
      
       printf("\nEste processo insere uma mensagem na Fila de Mensagens\n");
 
       msgctl(filaID, IPC_STAT, &fila);
       i = fila.msg_qnum;
 
       i++;
       printf("Digite a mensagem %d:\n", i);
       fgets(buffer,255,stdin);
       strcpy(msg.texto, buffer);
       msg.tipo = i;
       if(msgsnd(filaID, &msg, sizeof(msg), 0) == 0)
             printf("Mensagem %d enviada com sucesso\n\n", i);
       else{
                    printf("Erro no envio da mensagem %d\n", i);
                    exit(-1);
       }
       return 0;
}
