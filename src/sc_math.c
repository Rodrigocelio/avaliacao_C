#include "libc.h"
#include <limits.h>
#include <stdlib.h>

int sc_atoi(const char *nptr)
{
    int sign;
    int result;

    sign = 1;
    result = 0;
    while (*nptr == ' ' || (*nptr >= 9 && *nptr <= 13))
        nptr++;
    if (*nptr == '-' || *nptr == '+')
    {
        if (*nptr == '-')
            sign = -1;
        nptr++;
    }
    while (*nptr >= '0' && *nptr <= '9')
    {
        result = result * 10 + (*nptr - '0');
        nptr++;
    }
    return (result * sign);
}

static unsigned int count_digits(int n)
{
    unsigned int count;

    count = 0;
    if (n == 0)
        return (1);
    if (n < 0)
        count = 1;
    while (n != 0)
    {
        count++;
        n /= 10;
    }
    return (count);
}

char *sc_itoa(int n)
{
    char *str;
    unsigned int len;

    long n_long;

    len = count_digits(n);
    str = (char *)malloc(len + 1);
    if (!str)
        return (NULL);
    str[len] = '\0';
    if (n == 0)
        str[0] = '0';
    n_long = n;
    if (n_long < 0)
    {
        str[0] = '-';
        n_long = -n_long;
    }
    while (n_long > 0)
    {
        str[--len] = (n_long % 10) + '0';
        n_long /= 10;
    }
    return (str);
}
