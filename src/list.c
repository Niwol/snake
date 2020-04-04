#include "list.h"

typedef struct linkedElement_s
{
    void *data;
    struct linkedElement_s *next;
    struct linkedElement_s *previous;
} *LinkedElement;

struct list_s
{
    LinkedElement sentinel;
    int size;
};

List list_create()
{
    List l = malloc(sizeof(struct list_s));
    l->sentinel = malloc(sizeof(struct linkedElement_s));

    l->sentinel->data = NULL;
    l->sentinel->next = l->sentinel;
    l->sentinel->previous = l->sentinel;
    l->size = 0;

    return l;
}

void list_delite(List *l)
{
    while((*l)->size != 0)
    {
        free((*l)->sentinel->previous);
        (*l)->size--;
    }
    free((*l)->sentinel);
    free(*l);
    *l = NULL;
}

int list_size(List l)
{
    return l->size;
}

List list_pushBack(List l, void *data)
{
    LinkedElement new = malloc(sizeof(struct linkedElement_s));
    
    new->data = data;
    new->next = l->sentinel;
    new->previous = l->sentinel->previous;
    l->sentinel->previous->next = new;
    l->sentinel->previous = new;
    (l->size)++;

    return l;
}

List list_popBack(List l)
{
    LinkedElement del = l->sentinel->previous;

    l->sentinel->previous = del->previous;
    del->previous->next = l->sentinel;
    (l->size)--;

    free(del);

    return l;
}

void *list_back(List l)
{
    return l->sentinel->previous->data;
}

void list_dump(List l, simpleFunctor f)
{
    for(LinkedElement e = l->sentinel->next; e != l->sentinel; e = e->next)
        f(e->data);
}
