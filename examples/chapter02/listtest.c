#include <stdio.h>

#include "list.h"

int main()
{
    Nameval *list, *tmp;
    int size;

    list = newitem("Patrick", 33);
    list = addfront(list, newitem("Alice", 30));
    list = addend(list, newitem("Bob", 45));

    tmp = lookup(list, "Patrick");
    printf("%s: %d\n", tmp->name, tmp->value);

    apply(list, printnv, "%s: %d\n");

    size = 0;
    apply(list, inccounter, &size);
    printf("%d elements\n", size);

    delitem(list, "Patrick");

    size = 0;
    apply(list, inccounter, &size);
    printf("%d elements\n", size);

    freeall(list);

    return 0;
}
