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
/**
 * exlui um dado processo da tabela de processos.
 */
void remove_process(PROCESS *);

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
        current = current->next;
    }
    return current;
}

PROCESS *find_process(char *process_ID)
{
    PROCESS_IN_LIST *current = process_table->start;
    PROCESS *the_process = NULL;
    while (current != NULL)
    {
        if (current->process->process_ID != NULL && strcmp(process_ID, current->process->process_ID) == 0)
        {
            the_process = current->process;
            break;
        }
        current = current->next;
    }
    return the_process;
}

PROCESS *find_process_from_page(PAGE *page)
{
    PROCESS_IN_LIST *current = process_table->start;
    PROCESS *the_process = NULL;
    while (current != NULL)
    {
        if (current->process->process_ID != NULL && strcmp(current->process->process_ID, "") != 0)
        {
            for (int i = 0; i < NUMBER_OF_PAGES; i++)
            {
                if (&current->process->pages_table->pages[i] == page)
                {
                    return current->process;
                }
            }
        }
        current = current->next;
    }
    return NULL;
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
    PAGE **mapped_pages = malloc(sizeof(PAGE *) * number_mapped);
    int count = 0;
    for (int i = 0; i < NUMBER_OF_PAGES; i++)
    {
        if (process->pages_table->pages[i].present == PRESENT)
        {
            mapped_pages[count++] = &process->pages_table->pages[i];
        }
    }
    if (remove_set_of_pages(mapped_pages[0], number_mapped) == NULL)
    {
        return NULL;
    }
    process->status = IN_DISC;
    return process;
}

PROCESS *wake_up(PROCESS *process)
{
    printf("Levando Processo '%s' para a RAM...\n", process->process_ID);
    int frames = allocation_policy(process->image_size);
    int free_frames = get_number_of_free_frames();
    if (frames <= free_frames)
    {
        int mapped_pages_number = count_mapped_pages(process->pages_table);
        if (mapped_pages_number > free_frames)
        {
            mapped_pages_number = free_frames;
        }
        PAGE **mapped_pages = malloc(sizeof(PAGE *) * mapped_pages_number);
        for (int i = 0; i < mapped_pages_number; i++)
        {
            int *page_number_bits = get_first_present_page(process->pages_table);
            if (get_page_in_disc(process->swap_area, page_number_bits) == NULL)
            {
                return NULL;
            }
            PAGE *page_address = &process->pages_table->pages[get_decimal_from_bits(page_number_bits, PAGE_NUMBER_LEN)];
            if (map_page(process->pages_table,
                         page_address) == NULL)
            {
                return NULL;
            }
            mapped_pages[i] = page_address;
        }
        unmap_whole_pages_table(process->pages_table);
        for (int i = 0; i < mapped_pages_number; i++)
        {
            mapped_pages[i]->present = PRESENT;
        }
        if (mapped_pages_number < free_frames)
        {
            int count = frames - mapped_pages_number;
            for (int i = mapped_pages_number; i <= process->image_size / VIRTUAL_PAGE_SIZE; i++)
            {
                if (count-- > 0)
                {
                    int *page_number_bits = get_bits_from_decimal(i, PAGE_NUMBER_LEN);
                    if (get_page_in_disc(process->swap_area, page_number_bits) == NULL)
                    {
                        return NULL;
                    }
                    if (map_page(process->pages_table,
                                 &process->pages_table->pages[get_decimal_from_bits(page_number_bits, PAGE_NUMBER_LEN)]) == NULL)
                    {
                        return NULL;
                    }
                }
                else
                {
                    break;
                }
            }
        }
    }
    else
    {
        // liberar espaço na RAM
        if (force_sleep_for_space(frames) == 0)
        {
            return NULL;
        }
        // chamada recursiva, mas sempre será executado apenas mais uma vez.
        return wake_up(process);
    }
    process->status = IN_RAM;
    return process;
}

int force_sleep_for_space(int size)
{
    int free_space = get_number_of_free_frames();
    while (free_space < size)
    {
        PROCESS *chosen = choose_process_to_sleep();
        if ((go_to_sleep(chosen)) == NULL)
        {
            return 0;
        }
        free_space = get_number_of_free_frames();
    }
    return 1;
}

void print_process_situation()
{
    PROCESS_IN_LIST *current = process_table->start;
    int process_count = 0;
    int active = 0;
    while (current != NULL)
    {
        if (current->process->process_ID != NULL && strcmp(current->process->process_ID, "") != 0)
        {
            process_count++;
            if (current->process->status == IN_RAM)
            {
                active++;
            }
        }
        current = current->next;
    }
    printf("Quantidade de Processos existentes: %d\n", process_count);
    printf("Quantidade de Processos ativos na RAM: %d\n", active);
}

void reset_process(PROCESS *process)
{
    if (process != NULL)
    {
        printf("Excluindo processo...\n");
        free_swap_area(process->swap_area, process->image_size);
        free_pages_table(process->pages_table);
        remove_process(process);
    }
}

void remove_process(PROCESS *process)
{
    PROCESS_IN_LIST *current = process_table->start;
    PROCESS_IN_LIST *previous = NULL;
    while (current != NULL)
    {
        if (current->process->process_ID != NULL && strcmp(process->process_ID, current->process->process_ID) == 0)
        {
            current->process;
            break;
        }
        previous = current;
        current = current->next;
    }
    if (current != NULL)
    {
        if (previous == NULL)
        {
            process_table->start = current->next;
        }
        else
        {
            previous->next = current->next;
        }
        free(current->process);
        free(current);
    }
}

int send_page_to_disc_from_only_page(PAGE *page)
{
    PROCESS *process = find_process_from_page(page);
    if (process == NULL)
    {
        return 0;
    }
    int i = 0;
    for (; i < NUMBER_OF_PAGES; i++)
    {
        if (&process->pages_table->pages[i] == page)
        {
            break;
        }
    }
    if (send_page_to_disc(process->swap_area, page, get_bits_from_decimal(i, PAGE_NUMBER_LEN)) == NULL)
    {
        return 0;
    }
    return 1;
}