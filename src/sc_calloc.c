#include "libc.h"
#include <stdlib.h>
#include <stdint.h>

void *sc_calloc(size_t nmemb, size_t size)
{
    void *ptr;
    size_t total;

    if (nmemb == 0 || size == 0)
    {
        total = 0;
    }
    else
    {
        if (nmemb > SIZE_MAX / size)
            return (NULL);
        total = nmemb * size;
    }
    ptr = malloc(total);
    if (!ptr)
        return (NULL);
    sc_bzero(ptr, total);
    return (ptr);
}
