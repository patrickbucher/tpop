#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "list.h"


/* newitem: create anew item from name and value */
Nameval *newitem(char *name, int value)
{
    Nameval *newp;

    newp = (Nameval *) emalloc(sizeof(Nameval));
    newp->name = name;
    newp->value = value;
    newp->next = NULL;
    return newp;
}

/* addfront: add newp to front of listp */
Nameval *addfront(Nameval *listp, Nameval *newp)
{
    newp->next = listp;
    return newp;
}

/* addend: add newp to end of listp */
Nameval *addend(Nameval *listp, Nameval *newp)
{
    Nameval *p;

    if (listp == NULL) {
        return newp;
    }
    for (p = listp; p->next != NULL; p = p->next);
    p->next = newp;
    return listp;
}

/* lookup: sequential search for name ist listp */
Nameval *lookup(Nameval *listp, char *name)
{
    for ( ; listp != NULL; listp = listp->next) {
        if (strcmp(name, listp->name) == 0) {
            return listp;
        }
    }
    return NULL; /* no match */
}

/* apply: execute fn for each element of listp */
void apply(Nameval *listp, void (*fn)(Nameval*, void*), void *arg)
{
    for ( ; listp != NULL; listp = listp->next) {
        (*fn)(listp, arg); /* call the function */
    }
}

/* printnv: print name and value using format in arg
   usage: apply(nvlist, printenv, "%s: %x\n"); */
void printnv(Nameval *p, void *arg)
{
    char *fmt;
    fmt = (char *) arg;
    printf(fmt, p->name, p->value);
}

/* inccounter: increment counter *arg
   usage: apply(nvlist,inccounter, &n); */
void inccounter(Nameval *p,void *arg)
{
    int *ip;
    /* p is unused */
    ip = (int *) arg;
    (*ip)++;
}

/* freeall: free all elements of listp */
void freeall(Nameval *listp)
{
    Nameval *next;

    for ( ; listp != NULL; listp = next) {
        next = listp->next;
        /* assumes name is freed elsewhere */
        free(listp);
    }
}

/* delitem: delete first "name" from listp */
Nameval *delitem(Nameval *listp, char *name)
{
    Nameval *p, *prev;

    prev = NULL;
    for (p = listp; p != NULL; p = p->next) {
        if (strcmp(name, p->name) == 0) {
            if (prev == NULL) {
                listp = p->next;
            } else {
                prev->next = p->next;
            }
            free(p);
            return listp;
        }
        prev = p;
    }
    eprintf("delitem: %s not in list", name);
    return NULL; /* can't get here */
}

/* copy: copy an entire list */
Nameval *copy(Nameval *src)
{
    Nameval *cpy, *p;

    if (src == NULL) {
        return NULL;
    }
    cpy = copyitem(src);

    for (p = src->next; p != NULL; p = p->next) {
        addend(cpy, copyitem(p));
    }

    return cpy;
}

/* copyitem: copy a single item */
Nameval *copyitem(Nameval *orig)
{
    Nameval *new;
    size_t namelen;
    char *name;

    namelen = strlen(orig->name);
    name = (char*) malloc(sizeof(char) * namelen);
    strncpy(name, orig->name, namelen);
    new = newitem(name, orig->value);

    return new;
}

/* merge: combine the two given lists into one list by copying the items */
Nameval *merge(Nameval *first, Nameval *second)
{
    Nameval *new, *p;

    if (first == NULL || second == NULL) {
        return NULL;
    }

    new = copyitem(first);

    for (p = first->next; p != NULL; p = p->next) {
        addend(new, copyitem(p));
    }
    for (p = second; p != NULL; p = p->next) {
        addend(new, copyitem(p));
    }

    return new;
}

/* split: copy the items from list into first, and, starting from the item
   with the given name, to the second list. Both first and second are expected
   to point to NULL. */
void split(Nameval *list, char *name, Nameval **first, Nameval **second)
{
    Nameval *p, *target;
    int namelen;

    if (list == NULL || lookup(list, name) == NULL) {
        return;
    }

    *first = NULL;
    *second = NULL;
    target = NULL;
    namelen = strlen(name);

    for (p = list; p != NULL; p = p->next) {
        if (*second == NULL && strncmp(name, p->name, namelen) == 0) {
            // the first list element could be the splitter: no items in first
            *second = copyitem(p);
            target = *second;
        } else if (*first == NULL) {
            *first = copyitem(p);
            target = *first;
        } else if (target != NULL) {
            addend(target, copyitem(p));
        }
    }
}

/* insert_before: inserts add into list in front of the item with the name before */
Nameval *insert_before(Nameval *add, Nameval *list, char *before)
{
    Nameval *p, *prev;

    prev = NULL;
    for (p = list; p != NULL; p = p->next) {
        if (strcmp(p->name, before) == 0) {
            add->next = p;
            if (prev == NULL) {
                return add;
            } else {
                prev->next = add;
                return list;
            }
        }
        prev = p;
    }

    return list;
}

/* insert_after: inserts add into list as a successor of the item with the name after */
void *insert_after(Nameval *add, Nameval *list, char *after)
{
    Nameval *p;

    for (p = list; p != NULL; p = p->next) {
        if (strcmp(p->name, after) == 0) {
            add->next = p->next;
            p->next = add;
        }
    }
}

void *emalloc(size_t size)
{
    void *chunk = malloc(size);
    if (chunk == NULL) {
        exit(EXIT_FAILURE);
    }
    return chunk;
}

void eprintf(char *fmt, char *arg)
{
    printf(fmt, arg);
    exit(EXIT_FAILURE);
}
