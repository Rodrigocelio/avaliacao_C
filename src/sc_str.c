#include "libc.h"
#include <stdlib.h>

size_t sc_strlen(const char *s)
{
    size_t len;

    len = 0;
    while (s[len])
        len++;
    return (len);
}

size_t sc_strlcpy(char *dst, const char *src, size_t size)
{
    size_t i;

    if (size == 0)
        return (sc_strlen(src));
    i = 0;
    while (src[i] && i < size - 1)
    {
        dst[i] = src[i];
        i++;
    }
    dst[i] = '\0';
    return (sc_strlen(src));
}

size_t sc_strlcat(char *dst, const char *src, size_t size)
{
    size_t dst_len;
    size_t src_len;
    size_t i;

    dst_len = sc_strlen(dst);
    src_len = sc_strlen(src);
    if (size <= dst_len)
        return (size + src_len);
    i = 0;
    while (src[i] && dst_len + i < size - 1)
    {
        dst[dst_len + i] = src[i];
        i++;
    }
    dst[dst_len + i] = '\0';
    return (dst_len + src_len);
}

char *sc_strchr(const char *s, int c)
{
    while (*s)
    {
        if (*s == (char)c)
            return ((char *)s);
        s++;
    }
    if ((char)c == '\0')
        return ((char *)s);
    return (NULL);
}

char *sc_strrchr(const char *s, int c)
{
    const char *last;

    last = NULL;
    while (*s)
    {
        if (*s == (char)c)
            last = s;
        s++;
    }
    if ((char)c == '\0')
        return ((char *)s);
    return ((char *)last);
}

int sc_strncmp(const char *s1, const char *s2, size_t n)
{
    size_t i;

    i = 0;
    while (i < n && s1[i] && s2[i] && s1[i] == s2[i])
        i++;
    if (i == n)
        return (0);
    return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

char *sc_strnstr(const char *big, const char *little, size_t len)
{
    size_t i;
    size_t j;

    if (!*little)
        return ((char *)big);
    i = 0;
    while (big[i] && i < len)
    {
        j = 0;
        while (big[i + j] == little[j] && little[j] && i + j < len)
            j++;
        if (!little[j])
            return ((char *)&big[i]);
        i++;
    }
    return (NULL);
}

char *sc_strdup(const char *s)
{
    char *dup;
    size_t len;
    size_t i;

    if (!s)
        return (NULL);
    len = sc_strlen(s);
    dup = (char *)malloc(len + 1);
    if (!dup)
        return (NULL);
    i = 0;
    while (i <= len)
    {
        dup[i] = s[i];
        i++;
    }
    return (dup);
}
