#ifndef PROCESS_H
#define PROCESS_H

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
     * tamanho da imagem do processo que deve estar no disco.
     */
    int image_size;
    /**
     * indica se o processo está na memória principal (parcialmente ou totalmente)
     * ou se está no disco.
     */
    int status;
    // falta o endereço para o swap do processo
    // falta o endereço para a tabela de páginas
} PROCESS;

/**
 * cria um novo processo (PROCESS) vazio e o insere na tabela de processos.
 */
PROCESS *create_and_assign_process(void);
/**
 * retorna o processo que possui o process_ID fornecido para busca.
 */
PROCESS *find_process(char*);

#endif