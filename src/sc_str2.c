#include "libc.h"
#include <stdlib.h>

char *sc_substr(char const *s, unsigned int start, size_t len)
{
    char *sub;
    size_t s_len;
    size_t i;

    if (!s)
        return (NULL);
    s_len = sc_strlen(s);
    if (start >= s_len)
    {
        sub = (char *)malloc(1);
        if (!sub)
            return (NULL);
        sub[0] = '\0';
        return (sub);
    }
    if (len > s_len - start)
        len = s_len - start;
    sub = (char *)malloc(len + 1);
    if (!sub)
        return (NULL);
    i = 0;
    while (i < len)
    {
        sub[i] = s[start + i];
        i++;
    }
    sub[i] = '\0';
    return (sub);
}

char *sc_strjoin(char const *s1, char const *s2)
{
    char *join;
    size_t len1;
    size_t len2;
    size_t i;

    if (!s1 || !s2)
        return (NULL);
    len1 = sc_strlen(s1);
    len2 = sc_strlen(s2);
    join = (char *)malloc(len1 + len2 + 1);
    if (!join)
        return (NULL);
    i = 0;
    while (i < len1)
    {
        join[i] = s1[i];
        i++;
    }
    while (i < len1 + len2)
    {
        join[i] = s2[i - len1];
        i++;
    }
    join[i] = '\0';
    return (join);
}

static int in_set(char c, char const *set)
{
    while (*set)
    {
        if (*set == c)
            return (1);
        set++;
    }
    return (0);
}

char *sc_strtrim(char const *s, char const *set)
{
    char *trim;
    size_t start;
    size_t end;
    size_t i;

    if (!s || !set)
        return (NULL);
    start = 0;
    while (s[start] && in_set(s[start], set))
        start++;
    end = sc_strlen(s);
    while (end > start && in_set(s[end - 1], set))
        end--;
    trim = (char *)malloc(end - start + 1);
    if (!trim)
        return (NULL);
    i = 0;
    while (start < end)
    {
        trim[i] = s[start];
        i++;
        start++;
    }
    trim[i] = '\0';
    return (trim);
}

static size_t count_words(char const *s, char c)
{
    size_t count;

    count = 0;
    while (*s)
    {
        while (*s == c)
            s++;
        if (*s)
            count++;
        while (*s && *s != c)
            s++;
    }
    return (count);
}

static char *get_word(char const *s, char c)
{
    char *word;
    size_t len;
    size_t i;

    len = 0;
    while (s[len] && s[len] != c)
        len++;
    word = (char *)malloc(len + 1);
    if (!word)
        return (NULL);
    i = 0;
    while (i < len)
    {
        word[i] = s[i];
        i++;
    }
    word[i] = '\0';
    return (word);
}

static void free_split(char **arr, size_t i)
{
    while (i > 0)
    {
        i--;
        free(arr[i]);
    }
    free(arr);
}

char **sc_split(char const *s, char c)
{
    char **result;
    size_t words;
    size_t i;

    if (!s)
        return (NULL);
    words = count_words(s, c);
    result = (char **)malloc((words + 1) * sizeof(char *));
    if (!result)
        return (NULL);
    i = 0;
    while (*s)
    {
        while (*s == c)
            s++;
        if (*s)
        {
            result[i] = get_word(s, c);
            if (!result[i])
            {
                free_split(result, i);
                return (NULL);
            }
            i++;
        }
        while (*s && *s != c)
            s++;
    }
    result[i] = NULL;
    return (result);
}

char *sc_strmapi(char const *s, char (*f)(unsigned int, char))
{
    char *result;
    size_t len;
    size_t i;

    if (!s || !f)
        return (NULL);
    len = sc_strlen(s);
    result = (char *)malloc(len + 1);
    if (!result)
        return (NULL);
    i = 0;
    while (i < len)
    {
        result[i] = f((unsigned int)i, s[i]);
        i++;
    }
    result[i] = '\0';
    return (result);
}

void sc_striteri(char *s, void (*f)(unsigned int, char *))
{
    size_t i;

    if (!s || !f)
        return;
    i = 0;
    while (s[i])
    {
        f((unsigned int)i, &s[i]);
        i++;
    }
}
