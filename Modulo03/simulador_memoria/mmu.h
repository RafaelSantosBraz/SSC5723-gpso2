#ifndef MMU_H
#define MMU_H

#include "config.h"

/**
 * indica que a página foi modificada.
 */
#define MODIFIED 1
/**
 * indica que a página NÃO foi modificada.
 */
#define NOT_MODIFIED 0
/**
 * indica que a página possui atualmente um quadro de página mapeado.
 */
#define PRESENT 1
/**
 * indica que a página NÃO possui atualmente um quadro de página mapeado.
 */
#define NOT_PRESENT 0
/**
 * indica quantas páginas virtuais existem.
 */
#define NUMBER_OF_PAGES (VIRTUAL_MEM_SIZE / VIRTUAL_PAGE_SIZE)
/**
 * indica quantas quadros de página existem.
 */
#define NUMBER_OF_FRAMES (RAM_SIZE / FRAME_SIZE)
/**
 * indica quantas quadros bits são necessários para representar o número do quadro de página.
 */
#define FRAME_NUMBER_LEN get_bits_len(NUMBER_OF_FRAMES)

/**
 * representa a estrutura de uma página.
 */
typedef struct page
{
    /**
     * indica se a página foi referenciada. -- contador começa com 0 (valor 0 atribuído quando a página é criada).
     */
    int referenced;
    /**
     * indica se a página foi modificada.
     */
    int modified;
    /**
     * indica se a página possui uma moldura de página atualmente alocada na memória principal.
     */
    int present;
    /**
     * vetor de bits que representa o quadro de página que possui esta página alocada na memória principal.
     * O tamanho do vetor é alocado dinamicamente na criação da página.
     * O tamanho é constante e é indicado por FRAME_NUMBER_LEN.
     */
    int *frame_number;
} PAGE;

/**
 * representa a tabela de páginas de um processo.
 */
typedef struct pages_table
{
    /**
     * vetor de páginas do espaço de endereçamento virtual.
     * O vetor tem seu espaço alocado no momento da criação da tabela.
     * O tamanho do vetor é sempre constante para o tamanho da memória virtual 
     * -- Usar NUMBER_OF_PAGES
     */
    PAGE *pages;
} PAGES_TABLE;

/**
 * cria uma nova tabela de páginas para um processo e a retorna.
 */
PAGES_TABLE *create_and_assign_pages_table(void);

#endif