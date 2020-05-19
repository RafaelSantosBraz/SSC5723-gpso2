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
 * cria e inicializa um novo endereço através de sua representação binária.
 * Recebe o vetor de bits e seu tamanho.
 */
ADDRESS *get_address_from_bits(int *, int);
/**
 * retorna um vetor de char com a representação do endereço em bits.
 * Usado para exibição.
 */
char *get_bits_string_address(ADDRESS *);

#endif