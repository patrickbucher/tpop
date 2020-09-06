#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define NELEMS(v) (sizeof(v) / sizeof(v[0]))

int *permutationsort(int[], int);
int factorial(int);
bool is_ordered_asc(int[], int);
int **permutate(int[], int);

int main(int argc, char *argv[])
{
    int i, n;

    int array[] = {6, 9, 3, 5};
    n = NELEMS(array);
    int *sorted = permutationsort(array, n);

    for (i = 0; i < n; i++) {
        if (i > 0 && sorted[i-1] > sorted[i]) {
            printf("erroneous sorting at index %d/%d\n", i-1, i);
            exit(EXIT_FAILURE);
        }
        printf("%d ", sorted[i]);
    }
    putchar('\n');

    return 0;
}

// NOTICE: this is absolute insanity; memory is not freed, too...
int *permutationsort(int v[], int n)
{
    int **perms;
    int i, n_perms;

    n_perms = factorial(n);
    perms = (int**)malloc(sizeof(int*) * n_perms);

    perms = permutate(v, n);

    for (i = 0; i < n; i++) {
        if (is_ordered_asc(perms[i], n)) {
            return perms[i];
        }
    }

    return NULL;
}

int **permutate(int v[], int n)
{
    int exclude, i, j, w;
    int *remainder, **remainder_permutations, **permutations;

    permutations = (int**)malloc(sizeof(int*) * n);

    for (exclude = 0; exclude < n; exclude++) {
        remainder = (int*)malloc(sizeof(int) * (n-1));
        w = 0;
        for (i = 0; i < n; i++) {
            if (i != exclude) {
                remainder[w++] = v[i];
            }
        }
        remainder_permutations = permutate(remainder, n-1);
        for (i = 0; i < factorial(n-1); i++) {
            permutations[exclude] = (int*)malloc(sizeof(int) * n);
            permutations[exclude][0] = v[exclude];
            for (j = 0; j < n-1; j++) {
                // FIXME: this is broken
                permutations[exclude][j+1] = remainder_permutations[i][j];
            }
        }
    }

    return permutations;
}

bool is_ordered_asc(int v[], int n)
{
    int i;

    for (i = 0; i < n; i++) {
        if (i > 0 && v[i-1] > v[i]) {
            return false;
        }
    }

    return true;
}

int factorial(int n) {
    if (n <= 1) {
        return 1;
    } else {
        return n * factorial(n-1);
    }
}
