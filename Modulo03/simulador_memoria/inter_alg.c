#include "inter_alg.h"

#include "lru.h"
#include "clock.h"

PAGE *remove_set_of_pages(PAGE *pages_set, int size)
{
    switch (CURRENT_METHOD)
    {
    case LRU:
        // return função_implementada_em_LRU(pages_set, size);
        break;
    case CLOCK:
        // return função_implementada_em_CLOCK(pages_set, size);
        break;
    }
}

PAGE *remove_page(PAGE *page)
{
    switch (CURRENT_METHOD)
    {
    case LRU:
        // return função_implementada_em_LRU(page);
        break;
    case CLOCK:
        // return função_implementada_em_CLOCK(page);
        break;
    }
}