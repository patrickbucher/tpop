#include <stdio.h>
#include <stdlib.h>

#include "list.h"

int main()
{
    Nameval *list, *tmp, *cpy;
    int size;

    list = newitem("Patrick", 33);
    list = addfront(list, newitem("Alice", 30));
    list = addend(list, newitem("Bob", 45));

    puts("Lookup");
    tmp = lookup(list, "Patrick");
    printf("%s: %d\n", tmp->name, tmp->value);
    putchar('\n');

    puts("Print");
    apply(list, printnv, "%s: %d\n");
    putchar('\n');

    puts("Count");
    size = 0;
    apply(list, inccounter, &size);
    printf("%d elements\n", size);
    putchar('\n');

    puts("Delete");
    delitem(list, "Patrick");
    size = 0;
    apply(list, inccounter, &size);
    printf("%d elements\n", size);
    putchar('\n');

    puts("Copy");
    cpy = copy(list);
    apply(cpy, printnv, "%s: %d\n");
    putchar('\n');

    freeall(list);
    freeall(cpy);

    return 0;
}
