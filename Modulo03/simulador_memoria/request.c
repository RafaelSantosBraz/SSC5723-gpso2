#include "request.h"

#include <stdio.h>
#include "process.h"
#include "inter_alg.h"

/**
 * função auxiliar que imprime a situação atual do simulador:
 * Processos, RAM, tabela de páginas global e SWAP.
 */
void print_situation(void);

void receive_request(REQUEST *request)
{
    // incrementa o número de instruções executadas até o momento.
    inc_global_instruction_counter();
    switch (request->op)
    {
    case P:
    {

        break;
    }
    case I:
    {
        printf("Processo '%s' solicitando E/S para o dispositivo '%d' (%s)...\n",
               request->process_ID,
               request->number,
               get_bits_string_from_bits(get_bits_from_decimal(request->number, get_bits_len(1)), get_bits_len(1)));
        printf("Solicitação de E/S realizada!\n");
        break;
    }
    case R:
    {

        break;
    }
    case W:
    {

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
            process->process_ID = NULL;
            process->status = -1;
            break;
        }
        process->pages_table = create_and_assign_pages_table();
        if (process->pages_table == NULL)
        {
            printf("Não é possível criar o processo '%s'! Erro na tabela de páginas.\n", process->process_ID);
            process->process_ID = NULL;
            process->status = -1;
            break;
        }
        // o processo ainda não foi enviado para a RAM.
        process->status = IN_DISC;
        printf("Processo '%s' criado em disco.\n", process->process_ID);
        if (wake_up(process) == NULL)
        {
            printf("Não é possível criar o processo '%s' na RAM!\n", process->process_ID);
            process->process_ID = NULL;
            process->status = -1;
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
    printf("--------------------------------------------\n");
    printf("Resumo da situação atual do simulador.\n");
    print_process_situation();
    print_RAM_situation();
    print_global_page_situation();
    print_SWAP_situation();
    printf("--------------------------------------------\n");
}