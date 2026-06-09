#include "libc.h"

int sc_isalpha(int c)
{
    return ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'));
}

int sc_isdigit(int c)
{
    return (c >= '0' && c <= '9');
}

int sc_isalnum(int c)
{
    return (sc_isalpha(c) || sc_isdigit(c));
}

int sc_isascii(int c)
{
    return (c >= 0 && c <= 127);
}

int sc_isprint(int c)
{
    return (c >= 32 && c <= 126);
}

int sc_toupper(int c)
{
    if (c >= 'a' && c <= 'z')
        return (c - 32);
    return (c);
}

int sc_tolower(int c)
{
    if (c >= 'A' && c <= 'Z')
        return (c + 32);
    return (c);
}
