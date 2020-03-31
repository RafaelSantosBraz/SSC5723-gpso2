#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <signal.h>
#include <unistd.h>

int main(void)
{
    /*
	Este programa é o mesmo usado para demonstração do fork()
	Porém, foi adicionada uma chamada kill() para demonstrar sua execução
    */
    int i;
    pid_t pid;

	printf("pid = %d\n", getpid());

    if ((pid = fork()) < 0)
    {
        perror("fork");
        exit(1);
    }
    if (pid == 0)
    {
        //O código aqui dentro será executado no processo filho
	printf("\nExecutando o processo filho...\n");
	
	//kill(getpid(), 9);	
        printf("PID do Filho: %d\n", getpid());
    }
    else
    {
        //O código neste trecho será executado no processo pai
	printf("\nExecutando o processo pai:\n");
	/*
	    É enviado para a chamada kil() o pid do processo pai
            e um sinal de valor 9, que equivale ao sinal SIGKILL, e então o processo será "morto".
	    Assim, o restante do código não será executado pelo processo pai
	*/
	printf("\nProcesso pai morto: %d\n", kill(getpid(), 9));
        printf("pid do Pai: %d\n", getpid());
    }


    printf("Regiao comum\n\n");
    exit(0);
}
