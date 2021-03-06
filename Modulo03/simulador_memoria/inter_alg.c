#include "inter_alg.h"

#include "lru.h"
#include "clock.h"
#include <stdio.h>

PAGE *remove_set_of_pages(PAGE *pages_set, int size)
{
    switch (CURRENT_METHOD)
    {
    case LRU:
        return remove_set_of_pages_LRU(pages_set, size);
    case CLOCK:
        return remove_set_of_pages_CLOCK(pages_set, size);
    }
}

PAGE *remove_page(PAGE *page)
{
    switch (CURRENT_METHOD)
    {
    case LRU:
        return remove_page_LRU(page);
    case CLOCK:
        return remove_page_CLOCK(page);
    }
}

PAGE *insert_set_of_pages(PAGE *pages_set, int size)
{
    switch (CURRENT_METHOD)
    {
    case LRU:
        return insert_set_of_pages_LRU(pages_set, size);
    case CLOCK:
        return insert_set_of_pages_CLOCK(pages_set, size);
    }
}

PAGE *insert_page(PAGE *page)
{
    switch (CURRENT_METHOD)
    {
    case LRU:
        return insert_page_LRU(page);
    case CLOCK:
        return insert_page_CLOCK(page);
    }
}

void initialize_global_list()
{
    switch (CURRENT_METHOD)
    {
    case LRU:
        initialize_global_list_LRU();
        break;
    case CLOCK:
        initialize_global_list_CLOCK();
        break;
    }
}

int *remove_best_page()
{
    switch (CURRENT_METHOD)
    {
    case LRU:
        return remove_best_page_LRU();
    case CLOCK:
        return remove_best_page_CLOCK();
    }
}

void print_global_page_situation()
{
    printf("Quantidade de páginas virtuais na lista global: %d\n", get_number_mapped_pages());
}

int get_number_mapped_pages()
{
    switch (CURRENT_METHOD)
    {
    case LRU:
        return get_number_mapped_pages_LRU();
    case CLOCK:
        return get_number_mapped_pages_CLOCK();
    }
}