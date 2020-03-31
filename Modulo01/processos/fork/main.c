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

    if ((pid = fork()) < 0)
    {
        perror("fork");
        exit(1);
    }
    if (pid == 0)
    {
        //O código aqui dentro será executado no processo filho
	printf("Filho:\n");
	for (int j = 0; j <= 2; j++)
		printf("%d - filho\n", j);
	
	//kill(getpid(), 9);	
        printf("PID do Filho: %d\n", getpid());
    }
    else
    {
        //O código neste trecho será executado no processo pai
	printf("Pai:\n");
	for (int j = 0; j <= 2; j++)
		printf("%d - pai\n", j);

	//kill(getpid(), 9);
        printf("pid do Pai: %d\n", getpid());
    }


    printf("Regiao comum\n\n");
    scanf("%d", &i);
    exit(0);
}
