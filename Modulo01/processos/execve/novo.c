#include <stdio.h>
#include <unistd.h>

/*
* arquivo que será chamada pelo execve
*/

int main(int argc, char const *argv[])
{
    printf("Processo novo :O\n");
    /*
    * apenas verifica o número de argumentos e o exibe se algum valor foi passado.
    */
    if (argc != 2)
    {
        printf("Nenhum valor recebido :(\n");
    }
    else
    {
        printf("Valor recebido: %s\n", argv[1]);
    }
    /*
    // exibe o envp do do processo, o array de strings é terminado por NULL.     
    for (int c = 0; __environ[c] != NULL; c++)
    {
        printf("%s\n", envp[c]);
    }
    */
    return 0;
}