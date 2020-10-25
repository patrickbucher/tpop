#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "tree.h"

Nameval *create(char *name, int value)
{
    Nameval *node;
    int n;

    node = (Nameval*)malloc(sizeof(Nameval));
    n = strlen(name);
    node->name = (char*)malloc(sizeof(char) * (n + 1));
    strncpy(node->name, name, n);
    node->value = value;
    node->left = NULL;
    node->right = NULL;

    return node;
}

Nameval *insert(Nameval *treep, Nameval *newp)
{
    int cmp;

    if (treep == NULL) {
        return newp;
    }
    cmp = strcmp(newp->name, treep->name);
    if (cmp == 0) {
        printf("insert: duplicate entry %s ingored", newp->name);
    } else if (cmp < 0) {
        treep->left = insert(treep->left, newp);
    } else {
        treep->right = insert(treep->right, newp);
    }

    return treep;
}

Nameval *lookup(Nameval *treep, char *name)
{
    int cmp;

    if (treep == NULL) {
        return NULL;
    }
    cmp = strcmp(name, treep->name);
    if (cmp == 0) {
        return treep;
    } else if (cmp < 0) {
        return lookup(treep->left, name);
    } else {
        return lookup(treep->right, name);
    }
}

Nameval *nrlookup(Nameval *treep, char *name)
{
    int cmp;

    while (treep != NULL) {
        cmp = strcmp(name, treep->name);
        if (cmp == 0) {
            return treep;
        } else if (cmp < 0) {
            treep = treep->left;
        } else {
            treep = treep->right;
        }
    }
    return NULL;
}

void applyinorder(Nameval *treep,
                  void (*fn)(Nameval*, char*),
                  void *arg)
{
    if (treep == NULL) {
        return;
    }
    applyinorder(treep->left, fn, arg);
    (*fn)(treep, arg);
    applyinorder(treep->right, fn, arg);
}

void applypostorder(Nameval *treep,
                    void (*fn)(Nameval*, char*),
                    void *arg)
{
    if (treep == NULL) {
        return;
    }
    (*fn)(treep, arg);
    applypostorder(treep->left, fn, arg);
    applypostorder(treep->right, fn, arg);
}
