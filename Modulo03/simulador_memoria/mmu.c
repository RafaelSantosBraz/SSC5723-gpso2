#include "mmu.h"

#include <stdlib.h>
#include "address.h"

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