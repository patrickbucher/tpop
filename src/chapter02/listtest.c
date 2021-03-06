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
    putchar('\n');

    puts("Insert");
    europe = insert_before(newitem("Italy", 7), europe, "Switzerland");
    europe = insert_before(newitem("Portugal", 8), europe, "Luxemburg");
    insert_after(newitem("Spain", 9), europe, "Austria");
    insert_after(newitem("Bulgaria", 10), europe, "Spain");
    insert_after(newitem("Romania", 11), europe, "Luxemburg");
    apply(europe, printnv, "\t%s: %d\n");
    putchar('\n');

    list = addend(list, newitem("Charles", 67));
    list = addend(list, newitem("Dora", 53));
    list = addend(list, newitem("Elliot", 33));
    list = addend(list, newitem("Fiona", 21));

    puts("Reverse (recursively)");
    list = reverse_rec(list);
    apply(list, printnv, "\t%s: %d\n");
    putchar('\n');

    puts("Reverse (iteratively)");
    list = reverse_iter(list);
    apply(list, printnv, "\t%s: %d\n");
    putchar('\n');

    freeall(list);
    freeall(cpy);
    freeall(dach);
    freeall(benelux);
    freeall(europe);

    return 0;
}
