#include "config.h"

#include <math.h>
#include "mmu.h"

int get_bits_len(int size)
{
    return ((floor(log(size * 1024) / log(2)) + 1));
}

int allocation_policy(int image)
{
    int frames = floor((image / VIRTUAL_PAGE_SIZE) * ALLOCATION_PERCENT);
    if (frames == 0)
    {
        frames = 1;
    }
    int max_frames = floor(0.50 * NUMBER_OF_FRAMES);
    if (frames > max_frames)
    {
        frames = max_frames;
    }
    return frames;
}