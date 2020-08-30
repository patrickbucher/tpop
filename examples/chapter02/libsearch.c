#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N_ELEMS(array) (sizeof(array) / sizeof(array[0]))

typedef struct {
    char *key;
    int value;
} item;

int compare(const void *left, const void *right)
{
    return strcmp(((item*)left)->key, ((item*)right)->key);
}

int main()
{
    item scores[] = {
        {"Hamilton", 121},
        {"Verstappen", 93},
        {"Bottas", 85},
        {"Norris", 62},
        {"Leclerc", 59},
    };

    for (int i = 0; i < N_ELEMS(scores); i++) {
        printf("%-20s %4d\n", scores[i].key, scores[i].value);
    }

    item search, *found;
    search.key = "Leclerc";

    found = (item*)bsearch(&search, scores, N_ELEMS(scores), sizeof(scores[0]), compare);
    if (found) {
        printf("%-20s %4d\n", found->key, found->value);
    }

    return 0;
}
