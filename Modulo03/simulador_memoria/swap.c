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