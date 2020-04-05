#ifndef LIST_H
#define LIST_H

#include <stdio.h>
#include <stdlib.h>

typedef struct list_s *List;
typedef void(*simpleFunctor)(void*);


List list_create();
void list_delite(List *l);
int list_size(List l);
List list_pushBack(List l, void *data);
List list_pushFront(List l, void *data);
List list_insert(List l, int pos, void *data);
List list_popBack(List l);
List list_popFront(List l);
List list_remove(List l, int pos);
void *list_back(List l);
void *list_front(List l);
void *list_at(List l, int pos);
void list_dump(List l, simpleFunctor f);


#endif