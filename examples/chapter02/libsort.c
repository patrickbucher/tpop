#include <stdio.h>
#include <stdlib.h>

#define N_ELEMS(array) (sizeof(array) / sizeof(array[0]))

int compare(const void*, const void*);

int main()
{
    int numbers[] = {6, 3, 7, 1, 9, 8, 0, 4, 5, 2};

    for (int i = 0; i < N_ELEMS(numbers); i++) {
        printf("%d ", numbers[i]);
    }
    putchar('\n');

    qsort(numbers, N_ELEMS(numbers), sizeof(numbers[0]), compare);

    for (int i = 0; i < N_ELEMS(numbers); i++) {
        printf("%d ", numbers[i]);
    }
    putchar('\n');

    return 0;
}

int compare(const void *left, const void *right)
{
    return *(int*)left - *(int*)right;
}
