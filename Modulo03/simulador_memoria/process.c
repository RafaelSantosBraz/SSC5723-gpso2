#include "process.h"

#include <stdlib.h>
#include <string.h>

/**
 * representa um processo em lista encadeada.
 */
typedef struct process_in_list
{
    /**
     * o processo em si nesta posição da lista.
     */
    PROCESS *process;
    /**
     * ponteiro para o próximo processo na lista.
     */
    struct process_in_list *next;
} PROCESS_IN_LIST;

/**
 * estrutura da tabela de processos.
 */
typedef struct process_list
{
    /**
     * ponteiro para o início da tabela (lista encadeada).
     */
    PROCESS_IN_LIST *start;
} PROCESS_LIST;

/**
 * a tabela de processos.
 */
PROCESS_LIST *process_table = NULL;

/**
 * inicializa a tabela de processos.
 */
void initialize_list(void);
/**
 * retorna o último elemento da tabela de processos (lista).
 */
PROCESS_IN_LIST *find_last();

PROCESS *create_and_assign_process()
{
    PROCESS *process = malloc(sizeof(PROCESS));
    if (process_table == NULL)
    {
        initialize_list();
    }
    PROCESS_IN_LIST *last = find_last();
    PROCESS_IN_LIST *current = malloc(sizeof(PROCESS_IN_LIST));
    current->next = NULL;
    current->process = process;
    if (find_last == NULL)
    {
        process_table->start = current;
    }
    else
    {
        last->next = current;
    }
    return process;
}

void initialize_list()
{
    process_table = malloc(sizeof(PROCESS_LIST));
    process_table->start = NULL;
}

PROCESS_IN_LIST *find_last()
{
    PROCESS_IN_LIST *current = process_table->start;
    while (current != NULL)
    {
        if (current->next == NULL)
        {
            break;
        }
    }
    return current;
}

PROCESS *find_process(char *process_ID)
{
    PROCESS_IN_LIST *current = process_table->start;
    PROCESS *the_process = NULL;
    while (current != NULL)
    {
        if (strcmp(process_ID, current->process->process_ID) == 0)
        {
            the_process = current->process;
            break;
        }
        current = current->next;
    }
    return the_process;
}