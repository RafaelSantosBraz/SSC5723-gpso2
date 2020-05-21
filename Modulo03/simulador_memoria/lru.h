#ifndef LRU_H
#define LRU_H

#include "mmu.h"

/**
 * função que atualiza a ordenação da lista global de páginas.
 * Esta função é chamada automaticamente conforme a necessidade de execução do próprio LRU e está disponível 
 * para acesso externo apenas para alguma eventualidade.
 * -- A execução desta função implica em um grande custo computacional.
 */
void update_global_list_LRU(void);
/**
 * remove da lista global de páginas ativas as páginas informadas pelo vetor de páginas.
 * O último parâmetro indica o tamanho do vetor de páginas informado.
 * Se tudo der certo, o ponteiro para o vetor de páginas informado será retornado (!= NULL).
 * Se NULL for retornado, não foi possível remover alguma(s) das páginas.
 */
PAGE *remove_set_of_pages_LRU(PAGE *, int);
/**
 * remove da lista global de páginas ativas a página informada.
 * Se tudo der certo, o ponteiro para a página informada será retornado (!= NULL).
 * Se NULL for retornado, não foi possível remover a página.
 */
PAGE *remove_page_LRU(PAGE *);
/**
 * insere na lista global de páginas ativas as páginas informadas pelo vetor de páginas.
 * O último parâmetro indica o tamanho do vetor de páginas informado.
 * Se tudo der certo, o ponteiro para o vetor de páginas informado será retornado (!= NULL).
 * Se NULL for retornado, não foi possível inserir alguma(s) das páginas.
 */
PAGE *insert_set_of_pages_LRU(PAGE *, int);
/**
 * insere na lista global de páginas ativas a página informada.
 * Se tudo der certo, o ponteiro para a página informada será retornado (!= NULL).
 * Se NULL for retornado, não foi possível inserir a página.
 */
PAGE *insert_page_LRU(PAGE *);
/**
 * inicializa a lista global de páginas ativas.
 */
void initialize_global_list_LRU(void);
/**
 * Seção principal dos algortimos de substituição de páginas.
 * Esta função é acionada quando ocorrer uma falta de página e não existirem quadros de páginas livres.
 * A ideia dessa função é selecionar a melhor páginas (conforme o algoritmo em execução) para ser substituída.
 * O retorno é o número do quadro de página que foi liberado ao desmapear alguma página virtual ativa.
 * -- Esta função já implica na remoção da página desmapeada da lista global e a marcação do bit 'present'
 * da página desmapeada como NOT_PRESENT.
 * Se tudo der certo, o vetor de bits que representa o número do quadro de página liberado é retornado.
 * O tamanho do vetor de bits é constante e representado por FRAME_NUMBER_LEN.
 * Se NULL for retornado, não foi possível desmapear alguma página e o erro deve ser tratado.
 */
int *remove_best_page_LRU(void);
/**
 * retorna a quantidade de páginas que estão na lista global de páginas no momento.
 */
int get_number_mapped_pages_LRU(void);
#endif