#include "address.h"

#include <stdlib.h>
#include <math.h>

ADDRESS *get_address_from_decimal(unsigned long long decimal, int bits_size)
{
    ADDRESS *address = malloc(sizeof(ADDRESS));
    address->decimal = decimal;
    address->size = bits_size;
    address->bits = get_bits_from_decimal(decimal, bits_size);
    return address;
}

int *get_bits_from_decimal(unsigned long long decimal, int bits_size)
{
    int *bits = malloc(sizeof(int) * bits_size);
    unsigned long long mask = 1ULL << (bits_size - 1);
    for (int i = 0; i < bits_size; i++)
    {
        bits[i] = (decimal & mask) ? 1 : 0;
        decimal <<= 1;
    }
    return bits;
}

char *get_bits_string_address(ADDRESS *address)
{
    return get_bits_string_from_bits(address->bits, address->size);
}

ADDRESS *get_address_from_bits(int *bits, int size)
{
    ADDRESS *address = malloc(sizeof(ADDRESS));
    address->size = size;
    address->bits = bits;
    address->decimal = get_decimal_from_bits(bits, size);
    return address;
}

unsigned long long get_decimal_from_bits(int *bits, int size)
{
    unsigned long long decimal = 0;
    int expo = size - 1;
    for (int i = 0; i < size; i++)
    {
        decimal += bits[i] * pow(2, expo--);
    }
    return decimal;
}

char *get_bits_string_from_bits(int *bits, int size)
{
    char *formated = malloc(sizeof(char) * size + 1);
    for (int i = 0; i < size; i++)
    {
        formated[i] = bits[i] == 1 ? '1' : '0';
    }
    formated[size] = '\0';
    return formated;
}