#include "clock.h"

#include "clock.h"

#include <stdlib.h>

/**
 * representa o encapsulamento da página real para a lista do clock.
 */
typedef struct clock_page_element
{
    /**
     * ponteiro para a página virtual real.
     */
    PAGE *page;
    /**
     * ponteiro para o próximo elemento da lista global do LRU.
     */
    struct clock_page_element *next;
} CLOCK_PAGE_ELEMENT;

/**
 * representa a estrutura lista global de páginas.
 */
typedef struct clock_pages_list
{
    /**
     * Como é uma lista circular, ponteiro para último elemento da lista
     * Ponteiro para elemento mais antigo da lista
     */
    CLOCK_PAGE_ELEMENT *end;
    CLOCK_PAGE_ELEMENT *old;
} CLOCK_PAGES_LIST;

/**
 * representa a lista global de páginas.
 */
CLOCK_PAGES_LIST *global_list_CLOCK = NULL;

PAGE *insert_page_CLOCK(PAGE *page)
{
    CLOCK_PAGE_ELEMENT *element = malloc(sizeof(CLOCK_PAGE_ELEMENT));
    element->next = NULL;
    element->page = page;

    /** 
     * Se a lista for vazia:
     *  - End aponta para ele mesmo
     *  - Old aponta para end
    */
    if (global_list_CLOCK->end == NULL)
    {
        global_list_CLOCK->end = page;
        global_list_CLOCK->end->next = global_list_CLOCK->end;
        global_list_CLOCK->old = global_list_CLOCK->end;
    }

    element->next = global_list_CLOCK->end->next; //elemento aponta para início da lista
    global_list_CLOCK->end->next = element; //insere elemento
    global_list_CLOCK->end = element; //atualiza end

    return page;
}