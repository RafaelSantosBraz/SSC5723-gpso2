#ifndef SWAP_H
#define SWAP_H

#include "config.h"
#include "process.h"
#include "address.h"

/**
 * representa a área de troca de um processo em disco.
 * Guarda a imagem do processo em disco.
 */
typedef struct process_swap_area
{
    /**
     * ponteiro para o processo que é dono desta área de troca.
     */
    PROCESS *process;
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
 * cria e vincula uma nova área de troca em disco para o processo informado.
 */
PROCESS_SWAP_AREA *create_process_swap_area(PROCESS *);

#endif