#include "request.h"

#include <stdio.h>
#include "process.h"

void receive_request(REQUEST *request)
{
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
        process->status = IN_DISC;
        process->swap_area = create_process_swap_area(process->image_size);
        if (process->swap_area == NULL)
        {
            printf("Não é possível criar o processo '%s'! Erro na SWAP.\n", process->process_ID);
            break;
        }
        process->pages_table = create_and_assign_pages_table();
        printf("Processo '%s' criado.\n", process->process_ID);
        printf("%s\n", get_bits_string_address(process->swap_area->last_address));
        break;
    }
    }
}