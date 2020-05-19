#ifndef INTER_ALG_H
#define INTER_ALG_H

/**
 * O 'inter_alg' serve para criar uma interface entre os algoritmos de substituição de páginas
 * e o restante do sistema.
 * Todas as funções apenas chamam as funções correspondentes nos algoritmos reais (LRU e Clock).
 */

#include "mmu.h"

/**
 * remove da lista global de páginas ativas as páginas informadas pelo vetor de páginas.
 * O último parâmetro indica o tamanho do vetor de páginas informado.
 * Se tudo der certo, o ponteiro para o vetor de páginas informado será retornado (!= NULL).
 * Se NULL for retornado, não foi possível remover alguma(s) das páginas.
 */
PAGE *remove_set_of_pages(PAGE *, int);
/**
 * remove da lista global de páginas ativas a página informada.
 * Se tudo der certo, o ponteiro para a página informada será retornado (!= NULL).
 * Se NULL for retornado, não foi possível remover a página.
 */
PAGE *remove_page(PAGE *);
/**
 * insere na lista global de páginas ativas as páginas informadas pelo vetor de páginas.
 * O último parâmetro indica o tamanho do vetor de páginas informado.
 * Se tudo der certo, o ponteiro para o vetor de páginas informado será retornado (!= NULL).
 * Se NULL for retornado, não foi possível inserir alguma(s) das páginas.
 */
PAGE *insert_set_of_pages(PAGE *, int);
/**
 * insere na lista global de páginas ativas a página informada.
 * Se tudo der certo, o ponteiro para a página informada será retornado (!= NULL).
 * Se NULL for retornado, não foi possível inserir a página.
 */
PAGE *insert_page(PAGE *);
/**
 * inicializa a lista global de páginas ativas.
 */
void initialize_list(void);
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
int *remove_best_page(void);

#endif