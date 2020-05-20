#include "swap.h"

#include <stdlib.h>
#include <stdio.h>

/**
 * marca o uso atual da swap.
 */
int current_used_swap = 0;

int get_used_swap()
{
    return current_used_swap;
}

PROCESS_SWAP_AREA *create_process_swap_area(int image_size)
{
    PROCESS_SWAP_AREA *swap_area = NULL;
    int new_used_swap = current_used_swap + image_size;
    if (new_used_swap <= SECUNDARY_MEM_MAX_SIZE)
    {
        current_used_swap = new_used_swap;
        swap_area = malloc(sizeof(PROCESS_SWAP_AREA));
        swap_area->first_address = get_address_from_decimal(0, VIRTUAL_ADDRESS_SIZE);
        if (image_size > VIRTUAL_MEM_SIZE)
        {
            printf("O processo não pode ser alocado na área de troca! Tamanho do processo maior do que o permitido para endereçamento.\n");
            swap_area = NULL;
        }
        else
        {
            swap_area->last_address = get_address_from_decimal(image_size * 1024 - 1, VIRTUAL_ADDRESS_SIZE);
        }
    }
    else
    {
        printf("O processo não pode ser alocado na área de troca! Sem espaço suficiente na área de troca.\n");
    }
    return swap_area;
}

int *get_page_in_disc(PROCESS_SWAP_AREA *swap_area, int *page_number_bits)
{
    if (page_number_bits == NULL)
    {
        printf("A página não pode ser buscada no disco, pois o valor 'NULL' é inválido.\n");
        return NULL;
    }
    int page_number = get_decimal_from_bits(page_number_bits, PAGE_NUMBER_LEN);
    if (page_number >= swap_area->first_address->decimal && page_number <= swap_area->last_address->decimal)
    {
        printf("Página '%d' (%s) foi buscada no disco.\n",
               page_number,
               get_bits_string_from_bits(page_number_bits, PAGE_NUMBER_LEN));
        return page_number_bits;
    }
    else
    {
        printf("A página '%d' (%s) não pode ser buscada no disco! Endereço fora do escopo da imagem do processo.\n",
               page_number,
               get_bits_string_from_bits(page_number_bits, PAGE_NUMBER_LEN));
        return NULL;
    }
}

PAGE *send_page_to_disc(PROCESS_SWAP_AREA *swap_area, PAGE *virtual_page, int *page_number_bits)
{
    int page_number = get_decimal_from_bits(page_number_bits, PAGE_NUMBER_LEN);
    if (page_number >= swap_area->first_address->decimal && page_number <= swap_area->last_address->decimal)
    {
        printf("A página '%d' (%s) foi enviada para o disco.\n",
               page_number,
               get_bits_string_from_bits(page_number_bits, PAGE_NUMBER_LEN));
        virtual_page->modified = NOT_MODIFIED;
        return virtual_page;
    }
    else
    {
        printf("A página '%d' (%s) não pode ser enviada para o disco! Endereço fora do escopo da imagem do processo.\n",
               page_number,
               get_bits_string_from_bits(page_number_bits, PAGE_NUMBER_LEN));
        return NULL;
    }
}

PAGES_TABLE *send_whole_pages_table_to_disc(PROCESS_SWAP_AREA *swap_area, PAGES_TABLE *pages_table)
{
    printf("Enviando todas as págins modificadas do processo para o disco...\n");
    for (int i = 0; i < NUMBER_OF_PAGES; i++)
    {
        if (pages_table->pages[i].present == PRESENT && pages_table->pages[i].modified == MODIFIED)
        {
            if (send_page_to_disc(swap_area, &pages_table->pages[i], get_bits_from_decimal(i, PAGE_NUMBER_LEN)) == NULL)
            {
                return NULL;
            }
        }
    }
    return pages_table;
}

int **get_pages_set_in_disc(PROCESS_SWAP_AREA *swap_area, int **pages_set, int size)
{
    printf("Buscando conjunto de páginas no disco...\n");
    if (pages_set != NULL)
    {
        for (int i = 0; i < size; i++)
        {
            if (get_page_in_disc(swap_area, pages_set[i]) == NULL)
            {
                return NULL;
            }
        }
        return pages_set;
    }
    pages_set = malloc(sizeof(int *) * size);
    for (int i = 0; i < size; i++)
    {
        pages_set[i] = get_bits_from_decimal(i, PAGE_NUMBER_LEN);
        if (get_page_in_disc(swap_area, pages_set[i]) == NULL)
        {
            return NULL;
        }
    }
    return pages_set;
}