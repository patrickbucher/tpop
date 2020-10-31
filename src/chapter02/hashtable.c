#include <string.h>

#include "hashtable.h"

Nameval *symtab[NHASH]; /* a sumbol table */

Nameval *lookup(char *name, int create, int value)
{
    int h;
    Nameval *sym;

    h = hash(name);
    for (sym = symtab[h]; sym != NULL; sym = sym->next) {
        if (strcmp(name, sym->name) == 0) {
            return sym;
        }
    }
    if (create) {
        sum = (Nameval*)malloc(sizeof(Nameval));
        sym-> name = name; /* assumed allocated elsewhere */
        sym->value = value;
        sym->next = symtab[h];
        symtab[h] = sym;
    }
    return sym;
}
