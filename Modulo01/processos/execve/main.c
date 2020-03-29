#include <unistd.h>
#include <stdio.h>

/*
* arquivo principal para demonstrar a chamada execve.
*/

int main(int argc, char const *argv[])
{
    printf("Processo original :)\n");

    /*
    // exibe o envp do do processo, o array de strings é terminado por NULL.     
    for (int c = 0; __environ[c] != NULL; c++)
    {
        printf("%s\n", envp[c]);
    }
    */

    /*
    * caminho para o novo processo.
    */
    char *const name = "./novo.out";
    /*
    * um dos argumentos esperados pelo novo processo. 
    * Pode ser qualquer string. 
    * Se não desejar passar um valor, pode deixar NULL ou retirá-lo do código.
    */
    char *const value = "42";
    /*
    * array de argumentos que serão passados ao novo processo.
    */
    char *const new_argv[3] = {name, value, NULL};
    /*
    * executa a chamada de sistema execve para trocar o processo em execução pelo novo processo.
    * Nenhum retorno é esperado, apenas se ocorrer algum erro.
    * Parâmetro 1: caminho do novo programa.
    * Parâmetro 2: argumentos para o novo processo.
    * Parâmetro 3: o ambiente de usuário que o novo processo herdade (terá uma cópia).
    *   Obs: o "__environ" é a variável correta para acessar os dados do ambiente do usuário conforme o POSIX.1
    */
    int resp = execve(name, new_argv, __environ);
    /*
    * espera-se que esta linha não seja executada.
    */
    printf("%d\n", resp);
    return 0;
}
