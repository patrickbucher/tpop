#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NELEMS(v) (sizeof(v) / sizeof(v[0]))

int *permutationsort(int[], int);
int factorial(int);
bool is_ordered_asc(int[], int);
void permutate(int[], int, int**, int);

int main(int argc, char *argv[])
{
    int i, n;

    int array[] = {6, 0, 9, 3, 2, 5, 10, 7, 4, 1, 8};
    n = NELEMS(array);
    int *sorted = permutationsort(array, n);
    if (sorted == NULL) {
        printf("sorting of %d element array failed\n", n);
        exit(EXIT_FAILURE);
    }

    for (i = 0; i < n; i++) {
        if (i > 0 && sorted[i-1] > sorted[i]) {
            printf("erroneous sorting at index %d/%d\n", i-1, i);
            exit(EXIT_FAILURE);
        }
        printf("%d ", sorted[i]);
    }
    putchar('\n');

    free(sorted);

    return 0;
}

// NOTICE: this algorithm is absolute insanity
int *permutationsort(int v[], int n)
{
    int **perms, *sorted;
    int i, j, nperms, found;

    nperms = factorial(n);
    perms = (int**)malloc(sizeof(int*) * nperms);
    for (i = 0; i < nperms; i++) {
        perms[i] = (int*)malloc(sizeof(int*) * n);
        memset(perms[i], 0, sizeof(int) * n);
    }

    permutate(v, n, perms, nperms);

    found = -1;
    for (i = 0; i < nperms; i++) {
        if (is_ordered_asc(perms[i], n)) {
            found = i;
            break;
        }
    }

    sorted = NULL;
    if (found != -1) {
        sorted = (int*)malloc(sizeof(int) * n);
        memcpy(sorted, perms[found], sizeof(int) * n);
    }

    for (i = 0; i < nperms; i++) {
        free(perms[i]);
    }
    free(perms);

    return sorted;
}

void permutate(int v[], int n, int **perms, int nperms)
{
    int exclude, i, j, w;
    int *remainder, **remainder_perms;
    int nsubperms, exclude_offset;

    if (n <= 1) {
        perms[0][0] = v[0];
        return;
    }

    nsubperms = factorial(n-1);

    remainder_perms = (int**)malloc(sizeof(int*) * nsubperms);
    for (i = 0; i < nsubperms; i++) {
        remainder_perms[i] = (int*)malloc(sizeof(int) * (n-1));
        memset(remainder_perms[i], 0, sizeof(int) * (n-1));
    }

    for (exclude = 0; exclude < n; exclude++) {

        remainder = (int*)malloc(sizeof(int) * (n-1));
        memset(remainder, 0, sizeof(int) * (n-1));

        w = 0;
        for (i = 0; i < n; i++) {
            if (i != exclude) {
                remainder[w++] = v[i];
            }
        }

        permutate(remainder, n-1, remainder_perms, nsubperms);

        for (i = 0; i < nsubperms; i++) {
            exclude_offset = exclude * nsubperms + i;
            perms[exclude_offset][0] = v[exclude];
            for (j = 0; j < n-1; j++) {
                perms[exclude_offset][j+1] = remainder_perms[i][j];
            }
        }

        free(remainder);
    }

    for (i = 0; i < nsubperms; i++) {
        free(remainder_perms[i]);
    }
    free(remainder_perms);
}

bool is_ordered_asc(int v[], int n)
{
    int i;

    for (i = 1; i < n; i++) {
        if (v[i-1] > v[i]) {
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
