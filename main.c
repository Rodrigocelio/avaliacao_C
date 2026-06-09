#include "libc.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void demo_classification(void)
{
    printf("=== Classificacao e Conversao ===\n");
    printf("sc_isalpha('A'): %d\n", sc_isalpha('A'));
    printf("sc_isdigit('5'): %d\n", sc_isdigit('5'));
    printf("sc_isalnum('Z'): %d\n", sc_isalnum('Z'));
    printf("sc_isascii(200): %d\n", sc_isascii(200));
    printf("sc_isprint('\\n'): %d\n", sc_isprint('\n'));
    printf("sc_toupper('b'): %c\n", sc_toupper('b'));
    printf("sc_tolower('X'): %c\n", sc_tolower('X'));
    printf("sc_atoi(\"  -42abc\"): %d\n", sc_atoi("  -42abc"));
    printf("\n");
}

void demo_memory(void)
{
    char buf1[20];
    char buf2[20];

    printf("=== Manipulacao de Memoria ===\n");
    sc_memset(buf1, 'A', 10);
    buf1[10] = '\0';
    printf("sc_memset: %s\n", buf1);

    sc_bzero(buf1, 10);
    printf("sc_bzero (primeiro byte): %d\n", buf1[0]);

    sc_memcpy(buf2, "Hello", 6);
    printf("sc_memcpy: %s\n", buf2);

    sc_memmove(buf1, buf2, 6);
    printf("sc_memmove: %s\n", buf1);

    char *p = sc_memchr(buf1, 'l', 6);
    printf("sc_memchr('l'): %s\n", p ? p : "NULL");

    printf("sc_memcmp(\"abc\", \"abd\", 3): %d\n", sc_memcmp("abc", "abd", 3));
    printf("\n");
}

void demo_strings(void)
{
    char dst[20];

    printf("=== Manipulacao de Strings ===\n");
    printf("sc_strlen(\"Hello\"): %zu\n", sc_strlen("Hello"));

    sc_strlcpy(dst, "World", sizeof(dst));
    printf("sc_strlcpy: %s\n", dst);

    sc_strlcat(dst, "!!!", sizeof(dst));
    printf("sc_strlcat: %s\n", dst);

    printf("sc_strchr(\"teste\", 's'): %s\n", sc_strchr("teste", 's'));
    printf("sc_strrchr(\"abacate\", 'a'): %s\n", sc_strrchr("abacate", 'a'));
    printf("sc_strncmp(\"abc\", \"abd\", 2): %d\n", sc_strncmp("abc", "abd", 2));
    printf("sc_strnstr(\"Hello World\", \"World\", 11): %s\n",
           sc_strnstr("Hello World", "World", 11));

    char *dup = sc_strdup("Duplicated!");
    printf("sc_strdup: %s\n", dup);
    free(dup);
    printf("\n");
}

static char map_toupper(unsigned int i, char c)
{
    (void)i;
    return ((char)sc_toupper((unsigned char)c));
}

static void iter_tolower(unsigned int i, char *c)
{
    (void)i;
    *c = (char)sc_tolower((unsigned char)*c);
}

void demo_additional(void)
{
    char *sub;
    char *join;
    char *trim;
    char **split;

    printf("=== Funcoes Adicionais ===\n");

    sub = sc_substr("Hello World", 6, 5);
    printf("sc_substr: %s\n", sub);
    free(sub);

    join = sc_strjoin("Hello ", "World");
    printf("sc_strjoin: %s\n", join);
    free(join);

    trim = sc_strtrim("  \tHello  ", " \t");
    printf("sc_strtrim: \"%s\"\n", trim);
    free(trim);

    split = sc_split("um,dois,tres", ',');
    printf("sc_split:\n");
    for (int i = 0; split[i]; i++)
        printf("  [%d] %s\n", i, split[i]);
    for (int i = 0; split[i]; i++)
        free(split[i]);
    free(split);

    char *itoa = sc_itoa(-12345);
    printf("sc_itoa(-12345): %s\n", itoa);
    free(itoa);

    char *mapi = sc_strmapi("abc", &map_toupper);
    printf("sc_strmapi (toupper): %s\n", mapi);
    free(mapi);

    char buf[] = "ABC";
    sc_striteri(buf, &iter_tolower);
    printf("sc_striteri (tolower): %s\n", buf);
    printf("\n");
}

void demo_output(void)
{
    printf("=== Saida em File Descriptor ===\n");
    printf("sc_putchar_fd: ");
    sc_putchar_fd('X', 1);
    printf("\n");

    printf("sc_putstr_fd: ");
    sc_putstr_fd("Hello", 1);
    printf("\n");

    printf("sc_putendl_fd:\n  ");
    sc_putendl_fd("linha 1", 1);
    printf("  ");
    sc_putendl_fd("linha 2", 1);

    printf("sc_putnbr_fd: ");
    sc_putnbr_fd(42, 1);
    printf("\n\n");
}

static void print_content(void *content)
{
    printf("  -> %s\n", (char *)content);
}

static void *dup_content(void *content)
{
    return (sc_strdup((char *)content));
}

void demo_linked_list(void)
{
    t_list *list;
    t_list *mapped;

    printf("=== Lista Ligada (Bonus) ===\n");

    list = NULL;
    sc_lstadd_front(&list, sc_lstnew(sc_strdup("terceiro")));
    sc_lstadd_front(&list, sc_lstnew(sc_strdup("segundo")));
    sc_lstadd_front(&list, sc_lstnew(sc_strdup("primeiro")));
    sc_lstadd_back(&list, sc_lstnew(sc_strdup("quarto")));

    printf("sc_lstsize: %d\n", sc_lstsize(list));
    printf("sc_lstlast: %s\n", (char *)sc_lstlast(list)->content);
    printf("sc_lstiter:\n");
    sc_lstiter(list, &print_content);

    mapped = sc_lstmap(list, &dup_content, &free);
    printf("sc_lstmap (copia):\n");
    sc_lstiter(mapped, &print_content);

    sc_lstclear(&mapped, &free);
    sc_lstclear(&list, &free);
    printf("\n");
}

int main(void)
{
    printf("========================================\n");
    printf("  Projeto LibC - Demonstracao\n");
    printf("========================================\n\n");

    demo_classification();
    demo_memory();
    demo_strings();
    demo_additional();
    demo_output();
    demo_linked_list();

    printf("========================================\n");
    printf("  Todos os testes concluidos!\n");
    printf("========================================\n");
    return (0);
}
