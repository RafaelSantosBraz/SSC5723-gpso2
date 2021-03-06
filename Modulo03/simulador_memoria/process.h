#ifndef PROCESS_H
#define PROCESS_H

#include "swap.h"
#include "mmu.h"

/**
 * indica que o processo está suspenso na área de troca em disco.
 */
#define IN_DISC 0
/**
 * indica que o processo está ao menos parcialmente na memória principal.
 */
#define IN_RAM 1

/**
 * representa uma entrada na tabela de processos (simplificada)
 * com as informações necessárias para manter o processo com 
 * relação a alocação de memória.
 */
typedef struct process
{
    /**
     * guarda o ID completo do processo (e.g., P1 ou P7).
     */
    char *process_ID;
    /**
     * tamanho da imagem do processo que deve estar no disco (em KB).
     */
    int image_size;
    /**
     * indica se o processo está na memória principal (parcialmente ou totalmente)
     * ou se está no disco.
     */
    int status;
    /**
     * ponteiro para entrada da área do processo na área de troca (swap) no disco.
     */
    PROCESS_SWAP_AREA *swap_area;
    /**
     * ponteiro para a entrada da tabela de páginas do processo.
     */
    PAGES_TABLE *pages_table;
} PROCESS;

/**
 * cria um novo processo (PROCESS) vazio e o insere na tabela de processos.
 */
PROCESS *create_and_assign_process(void);
/**
 * retorna o processo que possui o process_ID fornecido para busca.
 */
PROCESS *find_process(char *);
/**
 * determina, por meio da política de suspensão de processos, qual o melhor processo para ser mandado ao disco,
 * tendo-se por objetivo abrir espaço na memória principal para um processo ser executado (novo ou retornado do disco).
 * -- Política atual: Processo IN_RAM que possui o maior número páginas mapeadas deve ser suspenso com o objetivo de evitar
 * ao máximo a falta de páginas do novo processo, já que a transferência de uma pequena ou grande quantidade de páginas para o disco
 * não difere muito significativamente.
 * Se NULL for retornado, nenhum processo está ativo na memória principal no momento.
 */
PROCESS *choose_process_to_sleep(void);
/**
 * realiza a suspensão de um processo o enviando para a área de troca no disco.
 * Esta função também já solicita a libera do mapa de memória local e global do processo.
 * Se tudo der certo, o ponteiro para o processo informado será retornado (!= NULL).
 * Se NULL for retornado, não foi possível suspender o processo e a situação deve ser tratada.
 * -- Baixa probabilidade de um erro ocorrer, pois o processo em execução possui todas as áreas reservadas para ele.
 */
PROCESS *go_to_sleep(PROCESS *);
/**
 * realiza a busca do processo na área de troca em disco de volta para a memória principal.
 * Esta função também já solicita a inclusão do mapa de memória local e global do processo.
 * Se tudo der certo, o ponteiro para o processo informado será retornado (!= NULL).
 * Se NULL for retornado, não foi possível acordar o processo e a situação deve ser tratada.
 */
PROCESS *wake_up(PROCESS *);
/**
 * função utilizada para "matar" um processo.
 * Utilizada especialmente quando um processo encontra um erro durante sua criação.
 */
void reset_process(PROCESS *);
/**
 * abre espaço na meória principal para entrada de um novo processo (ou wake up) quando a quantidade de quadros livres
 * não é suficiente para manter a política de alocação.
 * A função força os processo IN_RAM a irem para a SWAP.
 * A quantidade de processos que terão que dormir depende de quantos quadros devem ser liberados, este valor é o parâmetro 
 * da função.
 * Se tudo ocorrer bem, 1 será retornado.
 * Se algo de errado ocorrer, 0 será retornado.
 */
int force_sleep_for_space(int);
/**
 * exibe quantos processos existem atualmente.
 */
void print_process_situation(void);
/**
 * responsável por enviar uma página modificada para o disco.
 * Esta função é utilizada quando ocorre a necessidade uma uma substituição de página e é chamada pelo LRU e CLOCK.
 * Esta função deve ser chamada apenas quando sabe-se a página, mas não quem é o processo e a área de troca para ela.
 * Retorna 0 ou 1.
 */
int send_page_to_disc_from_only_page(PAGE*);
/**
 * retorna quem é processo dono de uma dada página.
 * NULL indica que esta página não pertence a nenhum processo.
 */
PROCESS *find_process_from_page(PAGE *);

#endif