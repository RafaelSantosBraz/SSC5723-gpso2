#ifndef ADDRESS_H
#define ADDRESS_H

/**
 * representa um endereço, seja ele virtual ou físico.
 * O tamanho e o vetor de bits é espeficicado no momento de criação.
 */
typedef struct address
{
    /**
     * vetor de bits que representa o endereço. Os bits são números inteiros.
     */
    int *bits;
    /**
     * indica quantos bits existem no vetor.
     */
    int size;
    /**
     * guarda a versão decimal do vetor de bits. Utilizado apenas para exibição.
     */
    unsigned long long decimal;
} ADDRESS;

/**
 * cria e inicializa um novo endereço através de sua representação em decimal informada.
 * O int indica qual o tamanho do vetor de bits a ser gerado, pois varia para o endereço lógico e físico.
 */
ADDRESS *get_address_from_decimal(unsigned long long, int);
/**
 * retorna um vetor de bits através de sua representação em decimal informada.
 * O int indica qual o tamanho do vetor de bits a ser gerado, pois varia para o endereço lógico e físico.
 */
int *get_bits_from_decimal(unsigned long long, int);
/**
 * retorna um número decimal que representa o vetor de bits informado.
 * O int indica qual o tamanho do vetor de bits informado.
 */
unsigned long long get_decimal_from_bits(int *, int);
/**
 * cria e inicializa um novo endereço através de sua representação binária.
 * Recebe o vetor de bits e seu tamanho.
 */
ADDRESS *get_address_from_bits(int *, int);
/**
 * retorna um vetor de char com a representação do endereço em bits.
 * Usado para exibição.
 */
char *get_bits_string_address(ADDRESS *);
/**
 * retorna um vetor de char que representa o vetor de bits informado.
 * O int é o tamanho do vetor de bits informado.
 * Usado para exibição.
 */
char *get_bits_string_from_bits(int *, int);
/**
 * retorna um vetor de char que representa um vetor de bits para um decimal informado.
 * O último parâmetro é responsável por indicar o tamanho do vetor de bits a ser gerado.
 */
char *get_bits_string_from_decimal(int, int);
#endif