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
List list_popBack(List l);
void *list_back(List l);
void list_dump(List l, simpleFunctor f);


#endif