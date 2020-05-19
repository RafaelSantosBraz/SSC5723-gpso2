#ifndef MMU_H
#define MMU_H

#include "config.h"
#include "address.h"

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
 * indica quantos bits são necessários para representar o número do quadro de página.
 */
#define FRAME_NUMBER_LEN get_bits_len(NUMBER_OF_FRAMES)
/**
 * indica quantos bits são necessários para representar o número da página.
 */
#define PAGE_NUMBER_LEN get_bits_len(NUMBER_OF_PAGES)

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
 * retorna a quantidade de quadros de página atualmente em uso, isto é, atrelados a alguma página virtual.
 * Se o vetor de status for NULL, ele será automaticamente inicializado.
 */
int get_number_of_used_frames(void);
/**
 * apenas aloca a memória para o vetor frames_status e marca todas as posições como NOT_PRESENT.
 */
void initialize_frames(void);
/**
 * marca o status do quadro de página informado (vetor de bits de seu número) com o valor indicado no último parâmetro.
 * Utiliza a mesma tag PRESENT ou NOT_PRESENT para indicar se está sendo ou usado ou não, respectivamente.
 * O tamanho do vetor é constante e é representando por FRAME_NUMBER_LEN.
 * Se tudo ocorrer conforme o esperado, o ponteiro informado será retornado (!= NULL).
 * Se NULL for retornado, o número do quadro não pertence ao escopo do número de quadros existentes.
 */
int *mark_frame(int *, int);
/**
 * cria uma nova tabela de páginas para um processo e a retorna.
 */
PAGES_TABLE *create_and_assign_pages_table(void);
/**
 * converte um dado endereço virtual em seu correspondente endereço físico com base na tabela de páginas atual.
 * O char representa se é uma operação de escrita ou leitura sobre o endereço solicitado.
 * O último parâmetro é usado para retorno da função, indicando qual o número da página virtual (em um vetor de bits),
 * que foi ou tentou ser acessada. O tamanho desse vetor é constante e é definido por PAGE_NUMBER_LEN.
 * -- Usar as tags R ou W já existentes.
 * Se o valor NULL for retornado e o último parâmetro for diferente de NULL, significa que ocorreu uma falta de página que precisa ser tratada.
 * Se o valor NULL for retornado e o último parâmetro também for NULL, significa que um erro ocorreu se segmentação que deve ser tratado.
 */
ADDRESS *map_to_physical_address(ADDRESS *, PAGES_TABLE *, char, int *);
#endif