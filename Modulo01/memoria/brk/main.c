#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

/*
* arquivo para testar a primitiva brk.
*/

int main(int argc, char const *argv[])
{
    /*
    * antes de alocar a memória com o brk, é necessário saber o atual ponteiro para o limite alocado 
    * de memória para o processo. Isso é feito pela sycall sbrk com o parâmetro 0.
    */
    void *program_break = sbrk(0);
    /*
    * como o objetivo do programa é manipular números inteiros, a conversão explícita do ponteiro facilita
    * o processo.
    */
    int *int_ptr = (int *)program_break;
    /*
    * Utiliza-se a sycall brk para movimentar o limite alocado de memória para o processo, ou seja, 
    * alocar ou desalocar memória para o processo. Essa chamada de sistema retorna 0 se a alteração
    * ocorrou e -1 quando algo deu erro.
    * Parâmetro 1: um ponteiro para o novo limite de memória do processo. Nesse exemplo alocou-se 
    * 4 espaços de int -- int_ptr + 3 -- para que o último se torne a nova fronteira.
    */
    int resp = brk(int_ptr + 3);
    /*
    * apenas verifica se o brk ocorreu da forma que deveria.
    */
    if (resp != 0)
    {
        printf("Não foi possível alocar a memória :(\n");
        return EXIT_FAILURE;
    }
    /*
    * requisição de 2 números ao usuário e seu armazenamento nos 2 primeiros espaços alocados.
    */
    printf("Informe o primeiro número: ");
    scanf("%d", int_ptr);
    printf("Informe o segundo número: ");
    scanf("%d", (int_ptr + 1));
    /*
    * realiza-se a soma dos números lidos e armazenamento do resultado no 3° espaço alocado.
    */
    *(int_ptr + 2) = *(int_ptr) + *(int_ptr + 1);
    /*
    * exibição do resultado armazenado.
    */
    printf("A soma dos dois números é: %d\n", *(int_ptr + 2));
    /*
    * utiliza-se o brk novamente para que os espaços de memória alocados sejam liberados.
    * Para isso, movimenta-se a barreira novamente para o program_break original.
    */
    resp = brk(program_break);    
    
    return 0;
}
