/* **************************************************************** */
/*                       Exemplo de Mailbox                         */
/*                    RECEBIMENTO DE MENSAGENS                      */
/*                             mb2.c                                */
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
 
       chave = ftok(".", 'B');
 
       filaID = msgget(chave, IPC_CREAT | 00700);
 
       if (filaID == -1)
       {
             printf("Erro na criação da fila de mensagens\n");
             return EXIT_FAILURE;
       }
      
       if(msgrcv(filaID, &msg, sizeof(msg), i, 0) < 0)
       {
             printf("Erro ao receber a mensagem\n");
             exit(-1);
       }else
             printf("Mensagem recebida: tipo %d %s\n", msg.tipo, msg.texto);
 
       return 0;
}
