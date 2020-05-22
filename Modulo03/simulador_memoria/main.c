#include <stdio.h>
#include "input_file.h"
#include "inter_alg.h"
#include "mmu.h"

/**
 * função para descrever as características fixas do simulador em sua criação.
 */
void print_defines_situation(void);

int main()
{
    print_defines_situation();
    initialize_global_list();
    read_input_file();
    return 0;
}

void print_defines_situation()
{
    printf("\n--------------------------------------------\n");
    printf("Características do simulador.\n");
    printf("Método de substituição de páginas atual: %s\n", CURRENT_METHOD == CLOCK ? "Relógio" : "LRU");
    printf("Tamanho da página virtual e quadros de página: %d\n", VIRTUAL_PAGE_SIZE);
    printf("Tamanho max. da RAM (tamanho / N° quadros): %d/%d\n", RAM_SIZE, NUMBER_OF_FRAMES);
    printf("Tamanho max. da memória virtual (tamanho / N° páginas): %d/%d\n", VIRTUAL_MEM_SIZE, NUMBER_OF_PAGES);
    printf("Tamanho max. da SWAP: %d\n", SECUNDARY_MEM_MAX_SIZE);
    printf("Tamanho do endereço virtual: %d\n", VIRTUAL_ADDRESS_SIZE);
    printf("Tamanho do endereço físico: %d\n", PHYSICAL_ADDRESS_SIZE);
    printf("--------------------------------------------\n");
}