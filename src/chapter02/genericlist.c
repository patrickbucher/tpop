#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "genericlist.h"

#define STRLEN 20

void printFloat(Item *item)
{
    printf("%.2f\n", *(float*)item->value);
}

void printString(Item *item)
{
    printf("%s\n", (char*)item->value);
}

int main()
{
    List *scores, *names;
    float first, second, third;
    char monkey[STRLEN], donkey[STRLEN], honkey[STRLEN];

    first = 3.14;
    second = 2.88;
    third = 7.42;

    strncpy(monkey, "San Pellegrino", STRLEN);
    strncpy(donkey, "Kristoffer", STRLEN);
    strncpy(honkey, "Hasler", STRLEN);

    scores = new_list((void*)&first);
    append(scores, (void*)&second);
    append(scores, (void*)&third);

    names = new_list((void*)&monkey);
    append(names, (void*)donkey);
    append(names, (void*)honkey);

    each(scores, printFloat);
    each(names, printString);

    del_list(scores);
    del_list(names);

    return 0;
}

List *new_list(void *value)
{
    List *list;
    Item *item;

    item = (Item*)malloc(sizeof(Item));
    item->value = value;
    item->next = NULL;

    list = (List*)malloc(sizeof(List));
    list->head = item;

    return list;
}

void del_list(List *list)
{
    Item *tmp, *last;

    last = NULL;
    for (tmp = list->head; tmp != NULL; tmp = tmp->next) {
        if (last != NULL) {
            free(last);
        }
        last = tmp;
    }
    if (last != NULL) {
        free(last);
    }

    free(list);
}

void append(List *list, void *value)
{
    Item *new_item, *tmp;
    
    new_item = (Item*)malloc(sizeof(Item));
    new_item->value = value;
    new_item->next = NULL;

    for (tmp = list->head; tmp != NULL; tmp = tmp->next) {
        if (tmp->next == NULL) {
            tmp->next = new_item;
            return;
        }
    }
}

void each(List *list, void (*func)(Item*))
{
    Item *tmp;

    for (tmp = list->head; tmp != NULL; tmp = tmp->next) {
        func(tmp);
    }
}
