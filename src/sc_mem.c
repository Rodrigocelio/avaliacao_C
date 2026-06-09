#include "libc.h"

void *sc_memset(void *s, int c, size_t n)
{
    unsigned char *p;
    size_t i;

    p = (unsigned char *)s;
    i = 0;
    while (i < n)
    {
        p[i] = (unsigned char)c;
        i++;
    }
    return (s);
}

void sc_bzero(void *s, size_t n)
{
    sc_memset(s, 0, n);
}

void *sc_memcpy(void *dest, const void *src, size_t n)
{
    unsigned char *d;
    const unsigned char *s;
    size_t i;

    d = (unsigned char *)dest;
    s = (const unsigned char *)src;
    i = 0;
    while (i < n)
    {
        d[i] = s[i];
        i++;
    }
    return (dest);
}

void *sc_memmove(void *dest, const void *src, size_t n)
{
    unsigned char *d;
    const unsigned char *s;
    size_t i;

    d = (unsigned char *)dest;
    s = (const unsigned char *)src;
    if (d < s)
    {
        i = 0;
        while (i < n)
        {
            d[i] = s[i];
            i++;
        }
    }
    else if (d > s)
    {
        i = n;
        while (i > 0)
        {
            i--;
            d[i] = s[i];
        }
    }
    return (dest);
}

void *sc_memchr(const void *s, int c, size_t n)
{
    unsigned char *p;
    size_t i;

    p = (unsigned char *)s;
    i = 0;
    while (i < n)
    {
        if (p[i] == (unsigned char)c)
            return (&p[i]);
        i++;
    }
    return (NULL);
}

int sc_memcmp(const void *s1, const void *s2, size_t n)
{
    const unsigned char *p1;
    const unsigned char *p2;
    size_t i;

    p1 = (const unsigned char *)s1;
    p2 = (const unsigned char *)s2;
    i = 0;
    while (i < n)
    {
        if (p1[i] != p2[i])
            return ((int)(p1[i] - p2[i]));
        i++;
    }
    return (0);
}
