#include "mmu.h"

#include <stdlib.h>
#include <stdio.h>
#include "request.h"

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

ADDRESS *map_to_physical_address(ADDRESS *virtual_address, PAGES_TABLE *table, char op, int *page_number_bits)
{
    ADDRESS *physical_address = NULL;
    page_number_bits = malloc(sizeof(int) * PAGE_NUMBER_LEN);
    for (int i = 0; i < PAGE_NUMBER_LEN; i++)
    {
        page_number_bits[i] = virtual_address->bits[i];
    }
    int page_number = get_decimal_from_bits(page_number_bits, PAGE_NUMBER_LEN);
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
            for (int i = FRAME_NUMBER_LEN; i < PHYSICAL_ADDRESS_SIZE; i++)
            {
                physical_bits[i] = virtual_address->bits[i];
            }
            physical_address = get_address_from_bits(physical_bits, PHYSICAL_ADDRESS_SIZE);
            if (op == R)
            {
                table->pages[page_number].referenced++;
            }
            else
            {
                // marca como referenciada também, pois se ela foi modificada teve que ser acessada.
                table->pages[page_number].referenced++;
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
        page_number_bits = NULL;
    }
    return physical_address;
}