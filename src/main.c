#include <stdio.h>
#include <stdlib.h>

#include "list.h"

void printInt(void *data)
{
    int *val = (int*)data;
    printf("%d ", *val);
}

int main()
{
    int tabVals[10] = {54, 6, 20, 1, 8, 95, 411, 2321, 5, 112};
    int *current;
    List l = list_create();

    printf("Test list\n\n");

    for(int i = 0;i < 10; i++)
    {
        current = &tabVals[i];
        printf("insert %d à %d\n", *current, i/2);
        list_insert(l, i/2, current);
    }

    printf("\n");
    printf("List (%d)\n", list_size(l));
    list_dump(l, printInt);
    printf("\n");

    for(int i = 0;i < 5; i++)
    {
        current = list_at(l, i);
        printf("remove %d\n", *current);
        list_remove(l, i);
    }
    
    printf("\n");
    printf("List (%d)\n", list_size(l));
    list_dump(l, printInt);
    printf("\n");

    return 0;
}