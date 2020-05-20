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
     * indica se a página foi referenciada. -- 'contador' começa com 0 (valor 0 atribuído quando a página é criada).
     * Quando a página é referenciada, a MMU troca automaticamente o valor deste campo para o contador 
     * global de instruções se o LRU está habilitado. Se o CLOCK está habiltado, o valor 1 é atribuído.
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
 * Retorna o contador global de instruções.
 * O contador global de instruções inicia com 0 e é incrementado automaticamente conforme novas requisições chegam
 * (incrementado no arquivo 'request').
 * Este contador é utilizado quando o algortimo LRU está habilitado.
 */
int get_global_instruction_counter(void);
/**
 * Incrementa em 1 o contador global de instruções.
 * O contador global de instruções inicia com 0 e é incrementado automaticamente conforme novas requisições chegam
 * (incrementado no arquivo 'request').
 * Este contador é utilizado quando o algortimo LRU está habilitado.
 */
void inc_global_instruction_counter(void);
/**
 * retorna a quantidade de quadros de página atualmente em uso, isto é, atrelados a alguma página virtual.
 * Se o vetor de status for NULL, ele será automaticamente inicializado.
 */
int get_number_of_used_frames(void);
/**
 * retorna a quantidade de quadros de página atualmente livres, isto é, NÃO atrelados a alguma página virtual.
 * Se o vetor de status for NULL, ele será automaticamente inicializado.
 */
int get_number_of_free_frames(void);
/**
 * retorna o número (vetor de bits) do primeiro quadro de páginas livre.
 * O tamanho do vetor é constante e representado por FRAME_NUMBER_LEN.
 * Se não existirem quadros livres, NULL será retornado.
 */
int *get_first_free_frame(void);
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
 * retorna o número (vetor de bits) da primeira página virtual ativa (está mapeada).
 * O tamanho do vetor é constante e representado por PAGE_NUMBER_LEN.
 * Se não existirem páginas mapeadas, NULL será retornado.
 */
int *get_first_present_page(PAGES_TABLE *);
/**
 * cria uma nova tabela de páginas para um processo e a retorna.
 */
PAGES_TABLE *create_and_assign_pages_table(void);
/**
 * realiza o mapeamento de uma página virtual em um quadro de página disponível.
 * A própria função determina qual o quadro apropriado para alocação da página virtual.
 * A função já realiza a alteração necessária no mapa de páginas local e global.
 * Se existir algum quadro disponível e a alocação ocorrer bem, o ponteiro para a tabela de páginas informada
 * será retornado (!= NULL).
 * Se NULL for retornado, não foi possível mapear a página informada.
 */
PAGES_TABLE *map_page(PAGES_TABLE *, PAGE *);
/**
 * realiza o mapeamento de um conjunto de páginas virtuais em quadros de páginas disponíveis.
 * A própria função determina quais quadros são apropriados para alocação.
 * A função já realiza a alteração necessária no mapa de páginas local e global.
 * O último parâmetro informa qual o tamanho do conjunto de páginas informado.
 * Se existir a quantidade de quadros disponíveis e a alocação ocorrer bem, o ponteiro para a tabela de páginas informada
 * será retornado (!= NULL).
 * Se NULL for retornado, não foi possível mapear as páginas informadas.
 */
PAGES_TABLE *map_pages_set(PAGES_TABLE *, PAGE *, int);
/**
 * converte um dado endereço virtual em seu correspondente endereço físico com base na tabela de páginas atual.
 * O char representa se é uma operação de escrita ou leitura sobre o endereço solicitado.
 * -- Usar as tags R ou W já existentes.
 * O último parâmetro é usado para retorno da função, indicando qual o número da página virtual (em um vetor de bits),
 * que foi ou tentou ser acessada. O tamanho desse vetor é constante e é definido por PAGE_NUMBER_LEN.
 * Se o valor NULL for retornado e o último parâmetro for diferente de NULL, significa que ocorreu uma falta de página que precisa ser tratada.
 * Se o valor NULL for retornado e o último parâmetro também for NULL, significa que um erro ocorreu se segmentação que deve ser tratado.
 */
ADDRESS *map_to_physical_address(ADDRESS *, PAGES_TABLE *, char, int *);
/**
 * retorna a quantidade de páginas ativas na tabela de páginas informada.
 * Páginas ativas são aquelas que levam para um quadro de página válido na memória principal.
 */
int count_mapped_pages(PAGES_TABLE *);
#endif