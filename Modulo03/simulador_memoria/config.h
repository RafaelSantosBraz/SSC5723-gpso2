#ifndef CONFIG_H
#define CONFIG_H

#define VIRTUAL_PAGE_SIZE 4096
#define FRAME_SIZE VIRTUAL_PAGE_SIZE
#define VIRTUAL_ADDRESS_SIZE 32
#define RAM_SIZE (FRAME_SIZE * 100)
#define SECUNDARY_MEM_MAX_SIZE (FRAME_SIZE * 1000)

#define LRU 0
#define CLOCK 1

#define CURRENT_METHOD LRU


#endif
