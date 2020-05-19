#ifndef PROCESS_H
#define PROCESS_H

#include "swap.h"

/**
 * indica que o processo está suspenso na área de troca em disco.
 */
#define IN_DISC 0
/**
 * indica que o processo está ao menos parcialmente na memória principal.
 */
#define IN_RAM 1

/**
 * representa uma entrada na tabela de processos (simplificada)
 * com as informações necessárias para manter o processo com 
 * relação a alocação de memória.
 */
typedef struct process
{
    /**
     * guarda o ID completo do processo (e.g., P1 ou P7).
     */
    char *process_ID;
    /**
     * tamanho da imagem do processo que deve estar no disco (em KB).
     */
    int image_size;
    /**
     * indica se o processo está na memória principal (parcialmente ou totalmente)
     * ou se está no disco.
     */
    int status;
    /**
     * ponteiro para entrada da área do processo na área de troca (swap) no disco.
     */
    PROCESS_SWAP_AREA *swap_area;
    // falta o endereço para a tabela de páginas
} PROCESS;

/**
 * cria um novo processo (PROCESS) vazio e o insere na tabela de processos.
 */
PROCESS *create_and_assign_process(void);
/**
 * retorna o processo que possui o process_ID fornecido para busca.
 */
PROCESS *find_process(char *);

#endif