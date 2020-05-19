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
        PROCESS *process = create_and_assign_process();
        process->process_ID = request->process_ID;
        process->image_size = request->number;
        // IN_RAM -> o processo novo deve ser enviado ao menos parcialmente para a memória principal.
        process->status = IN_RAM;
        process->swap_area = create_process_swap_area(process->image_size);
        if (process->swap_area == NULL)
        {
            printf("Não é possível criar o processo '%s'! Erro na SWAP.\n", process->process_ID);
            break;
        }
        process->pages_table = create_and_assign_pages_table();
        // política de alocação inicial.
        int free_frames = NUMBER_OF_FRAMES - get_number_of_used_frames();
        if (free_frames == 0)
        {
            PROCESS *chosen_process = choose_process_to_sleep();
            free_frames = count_mapped_pages(chosen_process->pages_table);
        }
        else
        {
        }
        printf("Processo '%s' criado.\n", process->process_ID);
        break;
    }
    }
}