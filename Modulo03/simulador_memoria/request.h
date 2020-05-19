#ifndef REQUEST_H
#define REQUEST_H

/**
 * tag de execução de uma instrução.
 */
#define P 'P'
/**
 * tag de E/S.
 */
#define I 'I'
/**
 * tag de leitura.
 */
#define R 'R'
/**
 * tag de escrita.
 */
#define W 'W'
/**
 * tag de criação de um processo.
 */
#define C 'C'

/**
 * estrutura que agrupa as informações de cada requisição para o 
 * simulador.
 */
typedef struct request
{
    /**
     * guarda o ID completo do processo (e.g., P1 ou P7).
     */
    char *process_ID;
    /**
     * identifica qual a tag de operação requisitada (e.g., R ou W).
     */
    char op;
    /**
     * um número que que foi passado como parâmetro para a "op" requisitada. 
     * O que ele representa está intimamente ligado ao significado da "op".
     */
    int number;
} REQUEST;

/**
 * recebe e trata uma requisição recebida chamando os módulos apropriados.
 */
void receive_request(REQUEST *);

#endif