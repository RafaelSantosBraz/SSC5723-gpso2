#include "request.h"

#include <stdio.h>
#include "process.h"

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

        break;
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
}