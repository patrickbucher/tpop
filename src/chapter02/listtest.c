#include <stdio.h>
#include <stdlib.h>

#include "list.h"

int main()
{
    Nameval *list, *tmp, *cpy, *dach, *benelux, *europe;
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

    puts("Merge");
    dach = newitem("Switzerland", 1);
    dach = addend(dach, newitem("Germany", 2));
    dach = addend(dach, newitem("Austria", 3));
    benelux = newitem("Belgium", 4);
    benelux = addend(benelux, newitem("Netherlands", 5));
    benelux = addend(benelux, newitem("Luxemburg", 6));
    europe = merge(dach, benelux);
    apply(europe, printnv, "%s: %d\n");
    putchar('\n');

    puts("Split");
    freeall(dach);
    freeall(benelux);
    split(europe, "Belgium", &dach, &benelux);
    puts("Dach:");
    apply(dach, printnv, "\t%s: %d\n");
    puts("Benelux:");
    apply(benelux, printnv, "\t%s: %d\n");

    freeall(list);
    freeall(tmp);
    freeall(cpy);
    freeall(dach);
    freeall(benelux);
    freeall(europe);

    return 0;
}
