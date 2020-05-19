#include "process.h"

#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <stdio.h>
#include "inter_alg.h"

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
    process->image_size = 0;
    process->process_ID = NULL;
    process->status = -1;
    process->swap_area = NULL;
    process->pages_table = NULL;
    if (process_table == NULL)
    {
        initialize_list();
    }
    PROCESS_IN_LIST *last = find_last();
    PROCESS_IN_LIST *current = malloc(sizeof(PROCESS_IN_LIST));
    current->next = NULL;
    current->process = process;
    if (last == NULL)
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

PROCESS *choose_process_to_sleep(void)
{
    PROCESS_IN_LIST *current = process_table->start;
    PROCESS *the_process = NULL;
    int most_number = INT_MIN;
    while (current != NULL)
    {
        if (current->process->process_ID != NULL && strcmp(current->process->process_ID, "") != 0)
        {
            if (current->process->status == IN_RAM)
            {
                int aux = count_mapped_pages(current->process->pages_table);
                if (aux > most_number)
                {
                    most_number = aux;
                    the_process = current->process;
                }
            }
        }
        current = current->next;
    }
    return the_process;
}

PROCESS *go_to_sleep(PROCESS *process)
{
    // tabela de páginas local anterior é mantida para que
    // a restauração eficiente possa ser aplicada em sua reentrada na RAM.
    printf("Suspendento o Processo '%s'...\n", process->process_ID);
    if (send_whole_pages_table_to_disc(process->swap_area, process->pages_table) == NULL)
    {
        return NULL;
    }
    // quadros de página liberados.
    for (int i = 0; i < NUMBER_OF_PAGES; i++)
    {
        if (process->pages_table->pages[i].present == PRESENT)
        {
            mark_frame(process->pages_table->pages[i].frame_number, NOT_PRESENT);
        }
    }
    int number_mapped = count_mapped_pages(process->pages_table);
    PAGE *mapped_pages = malloc(sizeof(PAGE) * number_mapped);
    int count = 0;
    for (int i = 0; i < NUMBER_OF_PAGES; i++)
    {
        if (process->pages_table->pages[i].present == PRESENT)
        {
            mapped_pages[count++] = process->pages_table->pages[i];
        }
    }
    if (remove_set_of_pages(mapped_pages, number_mapped) == NULL)
    {
        return NULL;
    }
    return process;
}