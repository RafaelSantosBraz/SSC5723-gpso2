#include "mmu.h"

#include <stdlib.h>
#include <stdio.h>
#include "request.h"
#include "inter_alg.h"

/**
 * vetor que marca, para cada quadro de página, se ele está atualmente atrelado a alguma página virtual,
 * isto é, se ele está sendo usado.
 * Utiliza a mesma tag PRESENT ou NOT_PRESENT para indicar se está sendo ou usado ou não, respectivamente.
 * O tamanho do vetor é constante e é representando por NUMBER_OF_FRAMES.
 */
int *frames_status = NULL;

/**
 * O contador global de instruções inicia com 0 e é incrementado automaticamente conforme novas requisições chegam
 * (incrementado no arquivo 'request').
 * Este contador é utilizado quando o algortimo LRU está habilitado.
 */
int global_instruction_counter = 0;

int get_global_instruction_counter()
{
    return global_instruction_counter;
}

void inc_global_instruction_counter()
{
    global_instruction_counter++;
}

void initialize_frames()
{
    frames_status = malloc(sizeof(int) * NUMBER_OF_FRAMES);
    for (int i = 0; i < NUMBER_OF_FRAMES; i++)
    {
        frames_status[i] = NOT_PRESENT;
    }
}

int get_number_of_used_frames()
{
    int count = 0;
    if (frames_status == NULL)
    {
        initialize_frames();
        return 0;
    }
    for (int i = 0; i < NUMBER_OF_FRAMES; i++)
    {
        count += frames_status[i];
    }
    return count;
}

int get_number_of_free_frames()
{
    return NUMBER_OF_FRAMES - get_number_of_used_frames();
}

int *mark_frame(int *frame_number_bits, int status)
{
    if (frames_status == NULL)
    {
        initialize_frames();
    }
    int frame_number = get_decimal_from_bits(frame_number_bits, FRAME_NUMBER_LEN);
    if (frame_number >= 0 && frame_number < NUMBER_OF_FRAMES)
    {
        frames_status[frame_number] = status;
        return frame_number_bits;
    }
    return NULL;
}

int *get_first_free_frame()
{
    if (get_number_of_free_frames() == 0)
    {
        return NULL;
    }
    int i = 0;
    for (; i < NUMBER_OF_FRAMES; i++)
    {
        if (frames_status[i] == NOT_PRESENT)
        {
            break;
        }
    }
    if (i < NUMBER_OF_FRAMES)
    {
        return get_bits_from_decimal(i, FRAME_NUMBER_LEN);
    }
    return NULL;
}

PAGES_TABLE *create_and_assign_pages_table()
{
    PAGES_TABLE *table = malloc(sizeof(PAGES_TABLE));
    table->pages = malloc(sizeof(PAGE) * NUMBER_OF_PAGES);
    for (int i = 0; i < NUMBER_OF_PAGES; i++)
    {
        table->pages[i].frame_number = get_bits_from_decimal(0, FRAME_NUMBER_LEN);
        table->pages[i].modified = NOT_MODIFIED;
        table->pages[i].present = NOT_PRESENT;
        table->pages[i].referenced = 0;
    }
    return table;
}

ADDRESS *map_to_physical_address(ADDRESS *virtual_address, PAGES_TABLE *table, char op, int **page_number_bits)
{
    ADDRESS *physical_address = NULL;
    *page_number_bits = malloc(sizeof(int) * PAGE_NUMBER_LEN);
    for (int i = 0; i < PAGE_NUMBER_LEN; i++)
    {
        (*page_number_bits)[i] = virtual_address->bits[i];
    }
    int page_number = get_decimal_from_bits((*page_number_bits), PAGE_NUMBER_LEN);
    if (page_number >= 0 && page_number < NUMBER_OF_PAGES)
    {
        if (table->pages[page_number].present == PRESENT)
        {
            int *physical_bits = malloc(sizeof(int) * PHYSICAL_ADDRESS_SIZE);
            // copia o número do quadro de página.
            for (int i = 0; i < FRAME_NUMBER_LEN; i++)
            {
                physical_bits[i] = table->pages[page_number].frame_number[i];
            }
            // copia o valor do deslocamento.
            int mov = PAGE_NUMBER_LEN;
            for (int i = FRAME_NUMBER_LEN; i < PHYSICAL_ADDRESS_SIZE; i++)
            {
                physical_bits[i] = virtual_address->bits[mov++];
            }
            physical_address = get_address_from_bits(physical_bits, PHYSICAL_ADDRESS_SIZE);
            // sempre marca como referenciada, nesse caso.
            switch (CURRENT_METHOD)
            {
            case LRU:
                table->pages[page_number].referenced = get_global_instruction_counter();
                break;
            case CLOCK:
                table->pages[page_number].referenced = 1;
                break;
            }
            if (op == W)
            {
                table->pages[page_number].modified = MODIFIED;
            }
        }
        else
        {
            printf("Falta de Página! Endereço Virtual '%llu' (%s). Página N° '%d'.\n",
                   virtual_address->decimal,
                   get_bits_string_address(virtual_address),
                   page_number);
        }
    }
    else
    {
        printf("O endereço virtual '%llu' (%s) não pertence ao espaço de endereçamento virtual.\n",
               virtual_address->decimal,
               get_bits_string_address(virtual_address));
        (*page_number_bits) = NULL;
    }
    return physical_address;
}

int count_mapped_pages(PAGES_TABLE *table)
{
    int count = 0;
    for (int i = 0; i < NUMBER_OF_PAGES; i++)
    {
        count += table->pages[i].present;
    }
    return count;
}

PAGES_TABLE *map_page(PAGES_TABLE *table, PAGE *page)
{
    if (page == NULL)
    {
        return NULL;
    }
    int *frame_number_bits = get_first_free_frame();
    if (frame_number_bits == NULL)
    {
        return NULL;
    }
    mark_frame(frame_number_bits, PRESENT);
    page->frame_number = frame_number_bits;
    page->modified = NOT_MODIFIED;
    page->present = PRESENT;
    page->referenced = 0;
    insert_page(page);
    return table;
}

PAGES_TABLE *map_pages_set(PAGES_TABLE *table, PAGE *pages_set, int size)
{
    if (size > get_number_of_free_frames())
    {
        return NULL;
    }
    for (int i = 0; i < size; i++)
    {
        if (map_page(table, &pages_set[i]) == NULL)
        {
            return NULL;
        }
    }
    return table;
}

int *get_first_present_page(PAGES_TABLE *table)
{
    for (int i = 0; i < NUMBER_OF_PAGES; i++)
    {
        if (table->pages[i].present == PRESENT)
        {
            return get_bits_from_decimal(i, PAGE_NUMBER_LEN);
        }
    }
    return NULL;
}

void unmap_whole_pages_table(PAGES_TABLE *table)
{
    for (int i = 0; i < NUMBER_OF_PAGES; i++)
    {
        table->pages[i].present = NOT_PRESENT;
    }
}

void free_pages_table(PAGES_TABLE *table)
{
    printf("Liberando tabela de páginas...\n");
    if (table != NULL && table->pages != NULL)
    {
        for (int i = 0; i < NUMBER_OF_PAGES; i++)
        {            
            if (table->pages[i].present == PRESENT)
            {
                if (remove_page(&table->pages[i]) == NULL)
                {
                    printf("Não foi possível remover a página '%d' (%s) da tabela global de páginas.\n",
                           i,
                           get_bits_string_from_decimal(i, PAGE_NUMBER_LEN));
                }
                mark_frame(table->pages[i].frame_number, NOT_PRESENT);
            }
        }
        free(table->pages);
        free(table);
    }
}

void print_RAM_situation()
{
    printf("Utilização dos quadros de página: %d/%d\n", get_number_of_used_frames(), NUMBER_OF_FRAMES);
}