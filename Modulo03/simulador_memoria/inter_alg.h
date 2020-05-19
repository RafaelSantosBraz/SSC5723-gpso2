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
#endif