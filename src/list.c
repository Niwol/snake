#include <assert.h>
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

bool list_empty(List l)
{
    return l->size == 0;
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

List list_pushFront(List l, void *data)
{
    LinkedElement new = malloc(sizeof(struct linkedElement_s));
    
    new->data = data;
    new->previous = l->sentinel;
    new->next = l->sentinel->next;
    l->sentinel->next->previous = new;
    l->sentinel->next = new;
    (l->size)++;

    return l;
}

List list_insert(List l, int pos, void *data)
{
    assert(pos <= l->size);

    LinkedElement new = malloc(sizeof(struct linkedElement_s));
    LinkedElement e = l->sentinel;

    while(pos > 0)
    {
        e = e->next;
        pos--;
    }

    new->data = data;
    new->previous = e;
    new->next = e->next;
    e->next->previous = new;
    e->next = new;
    (l->size)++;

    return l;
}

List list_popBack(List l)
{
    assert(l->size != 0);

    LinkedElement del = l->sentinel->previous;

    l->sentinel->previous = del->previous;
    del->previous->next = l->sentinel;
    (l->size)--;

    free(del);

    return l;
}

List list_popFront(List l)
{
    assert(l->size != 0);

    LinkedElement del = l->sentinel->next;

    l->sentinel->next = del->next;
    del->next->previous = l->sentinel;
    (l->size)--;

    free(del);

    return l;
}

List list_remove(List l, int pos)
{
    assert(pos < l->size);
    
    LinkedElement del = l->sentinel->next;

    while(pos > 0)
    {
        del = del->next;
        pos--;
    }

    del->next->previous = del->previous;
    del->previous->next = del->next;
    (l->size)--;

    free(del);
    return l;
}

void *list_back(List l)
{
    assert(l->size != 0);
    return l->sentinel->previous->data;
}

void *list_front(List l)
{
    assert(l->size != 0);
    return l->sentinel->next->data;
}

void *list_at(List l, int pos)
{
    assert(pos < l->size);
    LinkedElement e = l->sentinel->next;
    while(pos > 0)
    {
        e = e->next;
        pos--;
    }
    
    return e->data;
}

void list_dump(List l, simpleFunctor f)
{
    for(LinkedElement e = l->sentinel->next; e != l->sentinel; e = e->next)
        f(e->data);
}
