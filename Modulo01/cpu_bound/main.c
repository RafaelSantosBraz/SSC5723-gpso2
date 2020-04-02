#include <stdio.h>
#include <stdlib.h>

/*
* arquivo para demonstrar o comportamento de um processo CPU-bound.
* O programa espera receber um número inteiro por parâmetro (argv) e depois calcula a soma
* de todos os interios entre 0 e o número informado.
*/

int main(int argc, char const *argv[])
{
    /*
    * apenas verifica se o número foi informado.
    */
    if (argc != 2)
    {
        printf("O número final deve ser informado! :(\n");
        return EXIT_FAILURE;
    }
    /*
    * converte a strig em um número válido. A possibilidade de não ser um número foi ignorada.
    */
    int final_n = atoi(argv[1]);
    /*
    * verifica se o número é positivo para ser somado.
    */
    if (final_n < 0)
    {
        printf("Número tem que ser positivo! :(\n");
        return EXIT_FAILURE;
    }
    printf("Calculando a soma de todos os inteiros entre 0 e %d\n", final_n);    
    unsigned long long int sum = 0;
    /*
    * realiza a soma. Este trecho simboliza o tempo gasto com o uso da CPU neste tipo de processo.
    */
    for (int c = 0; c <= final_n; c++)
    {
        sum += c;
    }
    printf("Soma: %llu\n", sum);
    return 0;
}
