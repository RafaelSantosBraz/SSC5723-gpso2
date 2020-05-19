#ifndef SWAP_H
#define SWAP_H

#include "config.h"
#include "address.h"
#include "mmu.h"

/**
 * representa a área de troca de um processo em disco.
 * Guarda a imagem do processo em disco.
 */
typedef struct process_swap_area
{
    /**
     * ponteiro para o primeiro endereço válido desta área de troca.
     */
    ADDRESS *first_address;
    /**
     * ponteiro para o último endereço válido desta área de troca.
     */
    ADDRESS *last_address;
} PROCESS_SWAP_AREA;

/**
 * retorna a quantidade de memória atualmente usada na área de swap.
 */
int get_used_swap(void);
/**
 * cria e vincula uma nova área de troca em disco com o tamanho de imagem especificado.
 */
PROCESS_SWAP_AREA *create_process_swap_area(int);
/**
 * retorna a página solicita como um vetor de bits de seu número a partir da área de troca informada.
 * O último parâmetro é o vetor de bits que indica o número da página a ser buscado em disco.
 * O tamanho do vetor de bits informado e retornado é constante e é representado por PAGE_NUMBER_LEN.
 * Se tudo ocorrer conforme o esperado, será retornado o mesmo vetor de bits (!= NULL) informado.
 * Se o valor NULL for retornado, ocorreu uma falha de segmentação que deve ser tratada, pois a página não existe.
 */
int *get_page_in_disc(PROCESS_SWAP_AREA *, int *);
/**
 * envia uma página da memória principal para a área de troca em disco.
 * Esta função já altera o bit de modificação da página para NOT_MODIFIED, mas deixa o bit "present" como estava,
 * pois esta função apenas copia a página modificada para o disco, não exclui seu mapeamento.
 * Precisa receber o ponteiro para a página na memória principal.
 * O último parâmetro é o vetor de bits que indica o número da página.
 * O tamanho do vetor de bits informado é constante e é representado por PAGE_NUMBER_LEN.
 * Se tudo ocorrer conforme o esperado, será retornado o mesmo ponteiro (!= NULL) informado.
 * Se o valor NULL for retornado, a página não é válida para a imagem do processo.
 */
PAGE *send_page_to_disc(PROCESS_SWAP_AREA *, PAGE *, int *);
#endif