#include<string.h>
#include<stdio.h>
#include<unistd.h>
#include<sys/wait.h>
#include<sys/types.h>
#include<sys/shm.h>
 
int main()
{
       int ID;
       char *ptr_sh;
       char buffer[256];
 
       /* Bloco de Memória Compartilhada */
       ID = shmget(ID, 256, IPC_CREAT | 00700);
       if (ID == -1)
       {
             printf("Erro na criação do bloco de memória compartilhada\n");
             return -1;
       }
      
       if (fork() == 0)
       {
             printf("Processo Filho\n");
             ptr_sh = shmat(ID, NULL, 0);
            
             printf("Digite a mensagem para o Processo Pai:\n");
             fgets(buffer,255,stdin);
 
             strcpy(ptr_sh, buffer);
 
             shmdt(ptr_sh);
       }
       else
       {
             ptr_sh = shmat(ID, NULL, 0);
             wait(NULL);
 
             strcpy(buffer, ptr_sh);
 
             printf("O processo Pai recebeu a seguinte mensagem\n%s\n", buffer);
 
             shmdt(ptr_sh);
 
             shmctl(ID, IPC_RMID, NULL);
       }
       return 0;
}
