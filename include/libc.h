#ifndef LIBC_H
# define LIBC_H

# include <stddef.h>

typedef struct s_list
{
    void          *content;
    struct s_list *next;
} t_list;

/* Classification & Conversion */
int     sc_isalpha(int c);
int     sc_isdigit(int c);
int     sc_isalnum(int c);
int     sc_isascii(int c);
int     sc_isprint(int c);
int     sc_toupper(int c);
int     sc_tolower(int c);
int     sc_atoi(const char *nptr);

/* Memory manipulation */
void   *sc_memset(void *s, int c, size_t n);
void    sc_bzero(void *s, size_t n);
void   *sc_memcpy(void *dest, const void *src, size_t n);
void   *sc_memmove(void *dest, const void *src, size_t n);
void   *sc_memchr(const void *s, int c, size_t n);
int     sc_memcmp(const void *s1, const void *s2, size_t n);

/* String manipulation */
size_t  sc_strlen(const char *s);
size_t  sc_strlcpy(char *dst, const char *src, size_t size);
size_t  sc_strlcat(char *dst, const char *src, size_t size);
char   *sc_strchr(const char *s, int c);
char   *sc_strrchr(const char *s, int c);
int     sc_strncmp(const char *s1, const char *s2, size_t n);
char   *sc_strnstr(const char *big, const char *little, size_t len);
char   *sc_strdup(const char *s);

/* Dynamic allocation */
void   *sc_calloc(size_t nmemb, size_t size);

/* Additional functions */
char   *sc_substr(char const *s, unsigned int start, size_t len);
char   *sc_strjoin(char const *s1, char const *s2);
char   *sc_strtrim(char const *s, char const *set);
char  **sc_split(char const *s, char c);
char   *sc_itoa(int n);
char   *sc_strmapi(char const *s, char (*f)(unsigned int, char));
void    sc_striteri(char *s, void (*f)(unsigned int, char *));
void    sc_putchar_fd(char c, int fd);
void    sc_putstr_fd(char *s, int fd);
void    sc_putendl_fd(char *s, int fd);
void    sc_putnbr_fd(int n, int fd);

/* Bonus: linked list */
t_list *sc_lstnew(void *content);
void    sc_lstadd_front(t_list **lst, t_list *new);
int     sc_lstsize(t_list *lst);
t_list *sc_lstlast(t_list *lst);
void    sc_lstadd_back(t_list **lst, t_list *new);
void    sc_lstdelone(t_list *lst, void (*del)(void *));
void    sc_lstclear(t_list **lst, void (*del)(void *));
void    sc_lstiter(t_list *lst, void (*f)(void *));
t_list *sc_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));

#endif
