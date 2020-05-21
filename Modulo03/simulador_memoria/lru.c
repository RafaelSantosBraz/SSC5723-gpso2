#include "lru.h"

#include <stdlib.h>
#include <stdio.h>

/**
 * representa o encapsulamento da página real para a lista do LRU.
 */
typedef struct lru_page_element
{
    /**
     * ponteiro para a página virtual real.
     */
    PAGE *page;
    /**
     * ponteiro para o próximo elemento da lista global do LRU.
     */
    struct lru_page_element *next;
} LRU_PAGE_ELEMENT;

/**
 * representa a estrutura lista global de páginas.
 */
typedef struct lru_pages_list
{
    /**
     * ponteiro para o primeiro elemento da lista
     */
    LRU_PAGE_ELEMENT *start;
} LRU_PAGES_LIST;

/**
 * variável auxiliar para evitar atualizações desnecessárias da lista global.
 * Esta trava evita um desperdício enorme de recursos e tempo.
 * 1 indica que deve atualizar e 0 que não precisa.
 */
int has_to_update = 1;
/**
 * representa a lista global de páginas.
 */
LRU_PAGES_LIST *global_list_LRU = NULL;
/**
 * função auxiliar que faz a inserção de um elemento de página na lista global.
 * Retorna 0 ou 1.
 */
int insert_element_LRU(LRU_PAGE_ELEMENT *);
/**
 * função auxiliar que realiza a busca por um elemento de página na lista global através do ponteiro de página informado.
 * O último parâmetro é utilizado para retorno da função e indica qual é o elemento antecessor do elemento encontrado.
 * Retorna NULL se a página não existir na lista global.
 */
LRU_PAGE_ELEMENT *find_element(PAGE *, LRU_PAGE_ELEMENT *);

void update_global_list_LRU()
{
    if (has_to_update == 1)
    {
        LRU_PAGES_LIST *new_list = malloc(sizeof(LRU_PAGES_LIST));
        new_list->start = NULL;
        LRU_PAGES_LIST *previous_list = global_list_LRU;
        global_list_LRU = new_list;
        LRU_PAGE_ELEMENT *current = previous_list->start;
        int count = 0;
        while (current != NULL)
        {
            count++;
            current = current->next;
        }
        PAGE **all_pages = NULL;
        if (count > 0)
        {
            all_pages = malloc(sizeof(PAGE *) * count);
            current = previous_list->start;
            for (int i = 0; i < count; i++)
            {
                all_pages[i] = current->page;
                LRU_PAGE_ELEMENT *aux = current;
                current = current->next;
                free(aux);
            }
            insert_set_of_pages_LRU(all_pages[0], count);
        }
        free(all_pages);
    }
}

int insert_element_LRU(LRU_PAGE_ELEMENT *element)
{
    LRU_PAGE_ELEMENT *current = global_list_LRU->start;
    LRU_PAGE_ELEMENT *previous = NULL;
    while (current != NULL)
    {
        if (current->page->referenced <= element->page->referenced)
        {
            break;
        }
        previous = current;
        current = current->next;
    }
    if (current == NULL)
    {
        global_list_LRU->start = element;
        return 1;
    }
    if (previous == NULL)
    {
        element->next = global_list_LRU->start;
        global_list_LRU->start = element;        
        return 1;
    }
    element->next = current;
    previous->next = element;
    return 1;
}

PAGE *remove_set_of_pages_LRU(PAGE *pages_set, int size)
{
    update_global_list_LRU();
    has_to_update = 0;
    for (int i = 0; i < size; i++)
    {
        if (remove_page_LRU(&pages_set[i]) == NULL)
        {
            has_to_update = 1;
            return NULL;
        }
    }
    has_to_update = 1;
    return pages_set;
}

PAGE *remove_page_LRU(PAGE *page)
{
    update_global_list_LRU();
    LRU_PAGE_ELEMENT *previous = NULL;
    LRU_PAGE_ELEMENT *element = find_element(page, previous);
    if (element == NULL)
    {
        return NULL;
    }
    if (previous == NULL)
    {
        global_list_LRU->start = element->next;
    }
    else
    {
        previous->next = element->next;
    }
    free(element);
    return page;
}

LRU_PAGE_ELEMENT *find_element(PAGE *page, LRU_PAGE_ELEMENT *previous)
{
    previous = NULL;
    LRU_PAGE_ELEMENT *current = global_list_LRU->start;
    while (current != NULL)
    {
        if (current->page == page)
        {
            return current;
        }
        previous = current;
        current = current->next;
    }
    return NULL;
}

PAGE *insert_set_of_pages_LRU(PAGE *pages_set, int size)
{
    update_global_list_LRU();
    has_to_update = 0;
    for (int i = 0; i < size; i++)
    {
        if (insert_page_LRU(&pages_set[i]) == NULL)
        {
            has_to_update = 1;
            return NULL;
        }
    }
    has_to_update = 1;
    return pages_set;
}

PAGE *insert_page_LRU(PAGE *page)
{
    update_global_list_LRU();
    LRU_PAGE_ELEMENT *element = malloc(sizeof(LRU_PAGE_ELEMENT));
    element->next = NULL;
    element->page = page;
    if (insert_element_LRU(element) == 0)
    {
        return NULL;
    }
    return page;
}

void initialize_global_list_LRU()
{
    global_list_LRU = malloc(sizeof(LRU_PAGE_ELEMENT));
    global_list_LRU->start = NULL;
}

int *remove_best_page_LRU()
{
    update_global_list_LRU();
    has_to_update = 0;
    LRU_PAGE_ELEMENT *current = global_list_LRU->start;
    while (current != NULL)
    {
        if (current->next == NULL)
        {
            break;
        }
        current = current->next;
    }
    if (current == NULL)
    {
        has_to_update = 1;
        return NULL;
    }
    int *frame_number = current->page->frame_number;
    if (remove_page_LRU(current->page) == NULL)
    {
        has_to_update = 1;
        return NULL;
    }
    has_to_update = 1;
    return frame_number;
}

int get_number_mapped_pages_LRU()
{
    LRU_PAGE_ELEMENT *current = global_list_LRU->start;
    int count = 0;
    while (current != NULL)
    {
        count++;
        current = current->next;
    }
    return count;
}