#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <signal.h>
#include <unistd.h>

int main(void)
{
    int i;
    pid_t pid;

	printf("pid = %d\n", getpid());
	//a função getpid() retorna o identificador do processo pai, que já está em execução

    // A partir da chamada fork() o processo filho é criado
    // Se a chamada fork retornar um  valor negativo (-1), então algum erro ocorreu e o processo filho não é criado
    if ((pid = fork()) < 0)
    {
        perror("fork");
        exit(1);
    }
    if (pid == 0)  // A chamada fork retornar 0 no processo filho
    {
        //O código aqui dentro será executado no processo filho
	printf("\nExecutando o processo filho...\n")
		
        printf("PID do Filho: %d\n", getpid()); //exibe o PID do processo filho
    }
    else // No processo pai, a chamada fork não retorna -1 nem 0, mas sim o valor do PID do filho
    {
        //O código neste trecho será executado no processo pai
	printf("\nExecutando o processo pai...\n");

        printf("PID do Pai: %d\n", getpid()); //exibe o PID do processo pai
    }
    // Daqui em diante, o código é executado tanto pelo processo pai quanto pelo filho

    printf("Regiao comum\n\n");
    exit(0);   
}
