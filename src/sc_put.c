#include "libc.h"
#include <unistd.h>

void sc_putchar_fd(char c, int fd)
{
    write(fd, &c, 1);
}

void sc_putstr_fd(char *s, int fd)
{
    if (!s)
        return;
    write(fd, s, sc_strlen(s));
}

void sc_putendl_fd(char *s, int fd)
{
    if (!s)
    {
        write(fd, "\n", 1);
        return;
    }
    write(fd, s, sc_strlen(s));
    write(fd, "\n", 1);
}

static void putnbr_recursive(long n, int fd)
{
    if (n < 0)
    {
        sc_putchar_fd('-', fd);
        n = -n;
    }
    if (n >= 10)
        putnbr_recursive(n / 10, fd);
    sc_putchar_fd((n % 10) + '0', fd);
}

void sc_putnbr_fd(int n, int fd)
{
    putnbr_recursive((long)n, fd);
}
