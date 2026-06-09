#include "libc.h"
#include <stdlib.h>

t_list *sc_lstnew(void *content)
{
    t_list *node;

    node = (t_list *)malloc(sizeof(t_list));
    if (!node)
        return (NULL);
    node->content = content;
    node->next = NULL;
    return (node);
}

void sc_lstadd_front(t_list **lst, t_list *new)
{
    if (!lst || !new)
        return;
    new->next = *lst;
    *lst = new;
}

int sc_lstsize(t_list *lst)
{
    int count;

    count = 0;
    while (lst)
    {
        count++;
        lst = lst->next;
    }
    return (count);
}

t_list *sc_lstlast(t_list *lst)
{
    if (!lst)
        return (NULL);
    while (lst->next)
        lst = lst->next;
    return (lst);
}

void sc_lstadd_back(t_list **lst, t_list *new)
{
    t_list *last;

    if (!lst || !new)
        return;
    if (!*lst)
    {
        *lst = new;
        return;
    }
    last = sc_lstlast(*lst);
    last->next = new;
}

void sc_lstdelone(t_list *lst, void (*del)(void *))
{
    if (!lst)
        return;
    if (del)
        del(lst->content);
    free(lst);
}

void sc_lstclear(t_list **lst, void (*del)(void *))
{
    t_list *tmp;

    if (!lst || !del)
        return;
    while (*lst)
    {
        tmp = (*lst)->next;
        sc_lstdelone(*lst, del);
        *lst = tmp;
    }
    *lst = NULL;
}

void sc_lstiter(t_list *lst, void (*f)(void *))
{
    if (!lst || !f)
        return;
    while (lst)
    {
        f(lst->content);
        lst = lst->next;
    }
}

t_list *sc_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
    t_list *new_list;
    t_list *new_node;
    void *new_content;

    if (!lst || !f)
        return (NULL);
    new_list = NULL;
    while (lst)
    {
        new_content = f(lst->content);
        new_node = sc_lstnew(new_content);
        if (!new_node)
        {
            if (del)
            {
                del(new_content);
                sc_lstclear(&new_list, del);
            }
            return (NULL);
        }
        sc_lstadd_back(&new_list, new_node);
        lst = lst->next;
    }
    return (new_list);
}
