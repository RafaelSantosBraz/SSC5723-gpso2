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
} CLOCK_PAGES_LIST;

/**
 * representa a lista global de páginas.
 */
CLOCK_PAGES_LIST *global_list_CLOCK = NULL;

/**
 * função auxiliar que realiza a busca por um elemento de página na lista global através do ponteiro de página informado.
 * O último parâmetro é utilizado para retorno da função e indica qual é o elemento antecessor do elemento encontrado.
 * Retorna NULL se a página não existe na lista global.
 */
CLOCK_PAGE_ELEMENT *find_element(PAGE *, CLOCK_PAGE_ELEMENT *);

/** 
 * Função auxiliar para checar se a lista está vazia
*/
int list_empty();

void initialize_global_list_LRU()
{
    global_list_CLOCK = malloc(sizeof(CLOCK_PAGE_ELEMENT));
    global_list_CLOCK->end = NULL;
}

PAGE *insert_page_CLOCK(PAGE *page)
{
    CLOCK_PAGE_ELEMENT *element = malloc(sizeof(CLOCK_PAGE_ELEMENT));
    element->next = NULL;
    element->page = page;

    /** 
     * Se a lista for vazia:
     *  - End aponta para ele mesmo
    */
    if (list_empty())
    {
        global_list_CLOCK->end = element;
        global_list_CLOCK->end->next = global_list_CLOCK->end;
        return page;
    }
    element->next = global_list_CLOCK->end->next; //elemento aponta para início da lista
    global_list_CLOCK->end->next = element; //insere elemento
    global_list_CLOCK->end = element; //atualiza end

    return page;
}

PAGE *remove_page_CLOCK(PAGE *page)
{
    CLOCK_PAGE_ELEMENT *previous = NULL;
    CLOCK_PAGE_ELEMENT *element = find_element(page, previous);
    if (element == NULL)
    {
        return NULL;
    }

    if (previous == NULL) //Se elemento for o primeiro da lista
    {
        global_list_CLOCK->end->next = element->next;
    }
    else
    {
        previous->next = element->next;
    }

    if (element == element->next) //Se element for o único elemento da lista
    {
        global_list_CLOCK->end = NULL; //esvazia lista
    }
    
    free(element);
    return page;
}

CLOCK_PAGE_ELEMENT *find_element(PAGE *page, CLOCK_PAGE_ELEMENT *previous)
{
    previous = NULL;
    CLOCK_PAGE_ELEMENT *current = global_list_CLOCK->end->next;

    //Se lista estiver vazia
    if (list_empty())
    {
        return NULL;
    }

    do
    {
        if (current->page == page)
        {
            return current;
        }
        previous = current;
        current = current->next;
    } while (current != global_list_CLOCK->end->next);

    return NULL;
}

int list_empty(){
    if (global_list_CLOCK->end == NULL)
    {
        return 1;
    }
    return 0;
}

PAGE *remove_set_of_pages_CLOCK(PAGE *pages_set, int size)
{
    for (int i = 0; i < size; i++)
    {
        if (remove_page_CLOCK(&pages_set[i]) == NULL)
        {
            return NULL;
        }
    }
    return pages_set;
}

PAGE *insert_set_of_pages_CLOCK(PAGE *pages_set, int size)
{
    for (int i = 0; i < size; i++)
    {
        if (insert_page_CLOCK(&pages_set[i]) == NULL)
        {
            return NULL;
        }
    }
    return pages_set;
}

int get_number_mapped_pages_CLOCK()
{
    CLOCK_PAGE_ELEMENT *current = global_list_CLOCK->end->next;
    int count = 0;

    if(list_empty())
    {
        return count;
    }

    do
    {
        count++;
        current = current->next;
    } while (current != global_list_CLOCK->end->next);

    return count;
}