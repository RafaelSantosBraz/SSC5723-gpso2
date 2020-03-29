#include <stdio.h>
#include <sys/stat.h>
#include <stdlib.h>

int main(int argc, char const *argv[])
{
    const char *ls_command = "ls -l file.txt";
    const char *file_path = "./file.txt";

    printf("Permissões ANTES do chmod:\n");
    system(ls_command);

    struct stat st;
    __mode_t mode = S_IRWXU;

    //stat(file_path, &st);

    //mode = st.st_mode & 0777;
    // modify mode
    //mode &= ~(S_IWUSR); /* Clear this bit */
    //mode |= S_IXUSR;    /* Set this bit   */

    int resp = chmod(file_path, mode);

    if (resp != 0)
    {
        printf("Ocorreu um erro no chmod :( Cod: %d\n", resp);
    }
    else
    {
        printf("Permissões DEPOIS do chmod:\n");
        system(ls_command);
    }    
    return 0;
}
