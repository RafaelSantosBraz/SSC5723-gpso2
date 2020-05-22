#include "request.h"

#include <stdio.h>
#include "process.h"
#include "inter_alg.h"
#include <stdlib.h>

/**
 * função auxiliar que imprime a situação atual do simulador:
 * Processos, RAM, tabela de páginas global e SWAP.
 */
void print_situation(void);

void receive_request(REQUEST *request)
{
    // incrementa o número de instruções executadas até o momento.
    inc_global_instruction_counter();
    if (request->process_ID == NULL)
    {
        return;
    }
    switch (request->op)
    {
    case P:
    {
        printf("Processo '%s' solicitando a execução da instrução - operando - '%d' (%s)...\n",
               request->process_ID,
               request->number,
               get_bits_string_from_decimal(request->number, VIRTUAL_ADDRESS_SIZE));
        PROCESS *process = find_process(request->process_ID);
        if (process == NULL)
        {
            printf("Erro: Processo '%s' não existe!\n", request->process_ID);
            break;
        }
        if (process->status == IN_DISC)
        {
            if (wake_up(process) == NULL)
            {
                printf("Erro: Processo '%s' não pode ser acordado!\n", request->process_ID);
                break;
            }
        }
        int **page_number_bits = malloc(sizeof(int *));
        ADDRESS *physical_address = map_to_physical_address(get_address_from_decimal(request->number, VIRTUAL_ADDRESS_SIZE),
                                                            process->pages_table, request->op, page_number_bits);
        if (physical_address == NULL && (*page_number_bits) == NULL)
        {
            break;
        }
        if (physical_address == NULL && (*page_number_bits) != NULL)
        {
            int *frame_number_bits = NULL;
            if (get_number_of_free_frames() > 0)
            {
                frame_number_bits = get_first_free_frame();
            }
            else
            {
                frame_number_bits = remove_best_page();
            }
            if (frame_number_bits == NULL)
            {
                printf("Error: não foi possível substituir uma página virtual!\n");
                break;
            }
            if (get_page_in_disc(process->swap_area, (*page_number_bits)) == NULL)
            {
                break;
            }
            if (map_page(process->pages_table, &process->pages_table->pages[get_decimal_from_bits((*page_number_bits), PAGE_NUMBER_LEN)]) == NULL)
            {
                printf("Erro: não foi possível mapear a página!\n");
                break;
            }
            else
            {
                receive_request(request);
                return;
            }
            break;
        }
        printf("Processo '%s' executou a instrução - operando - '%d' (%s) \n\tno endereço físico '%lld' (%s) \n\tna quadro de página '%lld' (%s).\n",
               request->process_ID,
               request->number,
               get_bits_string_from_decimal(request->number, VIRTUAL_ADDRESS_SIZE),
               physical_address->decimal,
               get_bits_string_address(physical_address),
               physical_address->decimal / 1024 / FRAME_SIZE,
               get_bits_string_from_decimal(physical_address->decimal / 1024 / FRAME_SIZE, FRAME_NUMBER_LEN));
        break;
    }
    case I:
    {
        printf("Processo '%s' solicitando E/S para o dispositivo '%d' (%s)...\n",
               request->process_ID,
               request->number,
               get_bits_string_from_decimal(request->number, get_bits_len(1)));
        PROCESS *process = find_process(request->process_ID);
        if (process == NULL)
        {
            printf("Erro: Processo '%s' não existe!\n", request->process_ID);
            break;
        }
        printf("Solicitação de E/S realizada!\n");
        break;
    }
    case R:
    {
        printf("Processo '%s' solicitando leitura em '%d' (%s)...\n",
               request->process_ID,
               request->number,
               get_bits_string_from_decimal(request->number, VIRTUAL_ADDRESS_SIZE));
        PROCESS *process = find_process(request->process_ID);
        if (process == NULL)
        {
            printf("Erro: Processo '%s' não existe!\n", request->process_ID);
            break;
        }
        if (process->status == IN_DISC)
        {
            if (wake_up(process) == NULL)
            {
                printf("Erro: Processo '%s' não pode ser acordado!\n", request->process_ID);
                break;
            }
        }
        int **page_number_bits = malloc(sizeof(int *));
        ADDRESS *physical_address = map_to_physical_address(get_address_from_decimal(request->number, VIRTUAL_ADDRESS_SIZE),
                                                            process->pages_table, request->op, page_number_bits);
        if (physical_address == NULL && (*page_number_bits) == NULL)
        {
            break;
        }
        if (physical_address == NULL && (*page_number_bits) != NULL)
        {
            int *frame_number_bits = NULL;
            if (get_number_of_free_frames() > 0)
            {
                frame_number_bits = get_first_free_frame();
            }
            else
            {
                frame_number_bits = remove_best_page();
            }
            if (frame_number_bits == NULL)
            {
                printf("Error: não foi possível substituir uma página virtual!\n");
                break;
            }
            if (get_page_in_disc(process->swap_area, (*page_number_bits)) == NULL)
            {
                break;
            }
            if (map_page(process->pages_table, &process->pages_table->pages[get_decimal_from_bits((*page_number_bits), PAGE_NUMBER_LEN)]) == NULL)
            {
                printf("Erro: não foi possível mapear a página!\n");
                break;
            }
            else
            {
                receive_request(request);
                return;
            }
            break;
        }
        printf("Processo '%s' leu em '%d' (%s) \n\tno endereço físico '%lld' (%s) \n\tna quadro de página '%lld' (%s).\n",
               request->process_ID,
               request->number,
               get_bits_string_from_decimal(request->number, VIRTUAL_ADDRESS_SIZE),
               physical_address->decimal,
               get_bits_string_address(physical_address),
               physical_address->decimal / 1024 / FRAME_SIZE,
               get_bits_string_from_decimal(physical_address->decimal / 1024 / FRAME_SIZE, FRAME_NUMBER_LEN));
        break;
    }
    case W:
    {
        printf("Processo '%s' solicitando escrita em '%d' (%s)...\n",
               request->process_ID,
               request->number,
               get_bits_string_from_decimal(request->number, VIRTUAL_ADDRESS_SIZE));
        PROCESS *process = find_process(request->process_ID);
        if (process == NULL)
        {
            printf("Erro: Processo '%s' não existe!\n", request->process_ID);
            break;
        }
        if (process->status == IN_DISC)
        {
            if (wake_up(process) == NULL)
            {
                printf("Erro: Processo '%s' não pode ser acordado!\n", request->process_ID);
                break;
            }
        }
        int **page_number_bits = malloc(sizeof(int *));
        ADDRESS *physical_address = map_to_physical_address(get_address_from_decimal(request->number, VIRTUAL_ADDRESS_SIZE),
                                                            process->pages_table, request->op, page_number_bits);
        if (physical_address == NULL && (*page_number_bits) == NULL)
        {
            break;
        }
        if (physical_address == NULL && (*page_number_bits) != NULL)
        {
            int *frame_number_bits = NULL;
            if (get_number_of_free_frames() > 0)
            {
                frame_number_bits = get_first_free_frame();
            }
            else
            {
                frame_number_bits = remove_best_page();
            }
            if (frame_number_bits == NULL)
            {
                printf("Error: não foi possível substituir uma página virtual!\n");
                break;
            }
            if (get_page_in_disc(process->swap_area, (*page_number_bits)) == NULL)
            {
                break;
            }
            if (map_page(process->pages_table, &process->pages_table->pages[get_decimal_from_bits((*page_number_bits), PAGE_NUMBER_LEN)]) == NULL)
            {
                printf("Erro: não foi possível mapear a página!\n");
                break;
            }
            else
            {
                receive_request(request);
                return;
            }
            break;
        }
        printf("Processo '%s' escreveu em '%d' (%s) \n\tno endereço físico '%lld' (%s) \n\tna quadro de página '%lld' (%s).\n",
               request->process_ID,
               request->number,
               get_bits_string_from_decimal(request->number, VIRTUAL_ADDRESS_SIZE),
               physical_address->decimal,
               get_bits_string_address(physical_address),
               physical_address->decimal / 1024 / FRAME_SIZE,
               get_bits_string_from_decimal(physical_address->decimal / 1024 / FRAME_SIZE, FRAME_NUMBER_LEN));
        break;
    }
    case C:
    {
        printf("Criando o Processo '%s'...\n", request->process_ID);
        PROCESS *process = create_and_assign_process();
        process->process_ID = request->process_ID;
        process->image_size = request->number;
        process->swap_area = create_process_swap_area(process->image_size);
        if (process->swap_area == NULL)
        {
            printf("Não é possível criar o processo '%s'! Erro na SWAP.\n", process->process_ID);
            reset_process(process);
            break;
        }
        process->pages_table = create_and_assign_pages_table();
        if (process->pages_table == NULL)
        {
            printf("Não é possível criar o processo '%s'! Erro na tabela de páginas.\n", process->process_ID);
            reset_process(process);
            break;
        }
        if (process->image_size > VIRTUAL_MEM_SIZE)
        {
            printf("Não é possível criar o processo '%s'! Imagem maior do que a memória virtual.\n", process->process_ID);
            reset_process(process);
            break;
        }
        // o processo ainda não foi enviado para a RAM.
        process->status = IN_DISC;
        printf("Processo '%s' criado em disco.\n", process->process_ID);
        if (wake_up(process) == NULL)
        {
            printf("Não é possível criar o processo '%s' na RAM!\n", process->process_ID);
            reset_process(process);
            break;
        }
        printf("Processo '%s' criado completamente.\n", process->process_ID);
        break;
    }
    }
    print_situation();
}

void print_situation()
{
    printf("\n--------------------------------------------\n");
    printf("Resumo da situação atual do simulador.\n");
    print_process_situation();
    print_RAM_situation();
    print_global_page_situation();
    print_SWAP_situation();
    printf("--------------------------------------------\n");
}