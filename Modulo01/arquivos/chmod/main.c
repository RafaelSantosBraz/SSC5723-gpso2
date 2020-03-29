#include <stdio.h>
#include <sys/stat.h>
#include <stdlib.h>

/*
* arquivo para testar a chamada de sistema chmod.
* Observação interessante: O ambiente Linux no Windows não permite trocar as permissões de arquivos em /mnt.
*/

int main(int argc, char const *argv[])
{
    /*
    * commando ls para ser emitido para o terminal e comparar as permissões do arquivo.
    */
    const char *ls_command = "ls -l file.txt";
    /*
    * caminho para o arquivo de teste que terá suas permissões alteradas.
    */
    const char *file_path = "./file.txt";

    printf("Permissões ANTES do chmod:\n");
    /*
    * exibir as permissões do arquivo antes de serem alteradas.
    */
    system(ls_command);

    /*
    * __mode_t é um unsigned int que representa as permissões para o usuário, grupo e outros.
    * No exemplo, são atribuídas as permissões r/w/x para o usuário, nenhuma permissão para o grupo e r/w para outros.
    * Essas definições são encontradas em stat.h.
    */
    __mode_t mode = S_IRWXU | S_IROTH | S_IWOTH;

    /*
    * executa a chamada de sistema chmod para alterar as permissões (modo) do arquivo.
    * Parâmetro 1: caminho do arquivo.
    * Parâmetro 2: o unsigned int que representa as novas permissões combinadas.
    */
    int resp = chmod(file_path, mode);

    /*
    * verifica se houve algum erro (-1) ou se ocorrou conforme o esperado (0).
    */
    if (resp != 0)
    {
        printf("Ocorreu um erro no chmod :( Cod: %d\n", resp);
    }
    else
    {
        printf("Permissões DEPOIS do chmod:\n");
        /*
        * exibe as permissões do arquivo após o chmod ser executado corretamente.
        */
        system(ls_command);
    }
    return 0;
}
