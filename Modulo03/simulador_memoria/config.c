#include "config.h"

#include <math.h>
#include "mmu.h"
#include <stdio.h>

int get_bits_len(int size)
{
    return ((floor(log(size * 1024) / log(2)) + 1));
}

int get_bits_len_decimal(int size)
{
    return ((floor(log(size) / log(2)) + 1));
};

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
    if (frames == 0)
    {
        frames = 1;
    }
    return frames;
}