#ifndef CONFIG_H
#define CONFIG_H

/**
 * retorna a quantidade de bits necessária para representar uma quantidade de memória em KB.
 */
int get_bits_len(int);

/**
 * define o tamanho da página virtual em KB (e.g., 4 KB).
 */
#define VIRTUAL_PAGE_SIZE 4
/**
 * define o tamanho do quadro/moldura de página em KB (e.g., 4 KB). 
 * -- mantenha o mesmo que o virtual.
 */
#define FRAME_SIZE VIRTUAL_PAGE_SIZE
/**
 * define o tamanho total da memória principal (e.g., 100 molduras de página). 
 * -- múltiplo dos frames.
 */
#define RAM_SIZE (FRAME_SIZE * 100)
/**
 * define o tamanho da área de troca (swap) da memória secundária (e.g., 1000 molduras de página). 
 * -- múltiplo dos frames.
 */
#define SECUNDARY_MEM_MAX_SIZE (FRAME_SIZE * 10000)
/**
 * define o tamanho total da memória virtual (e.g., 200 páginas virtuais). 
 * -- múltiplo das páginas.
 */
#define VIRTUAL_MEM_SIZE (VIRTUAL_PAGE_SIZE * 2000)
/**
 * define o tamanho do endereço virtual (e.g., 32 bits). 
 * -- deve ser capaz de endereçar toda a memória virtual.
 * -- calculado automaticamente para atender ao tamanho ideal.
 */
#define VIRTUAL_ADDRESS_SIZE get_bits_len(VIRTUAL_MEM_SIZE)
/**
 * define o tamanho do endereço físico (e.g., 32 bits). 
 * -- deve ser capaz de endereçar toda a memória física real.
 */
#define PHYSICAL_ADDRESS_SIZE get_bits_len(RAM_SIZE)

#define LRU 0
#define CLOCK 1

#define CURRENT_METHOD LRU

#endif
