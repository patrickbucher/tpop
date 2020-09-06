#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define N_ELEMS(array) (sizeof(array) / sizeof(array[0]))

void quicksort(int[], int);
void swap(int[], int, int);

int main(int argc, char *argv[])
{
    int i, n;
    int *array;
    clock_t before, after;
    double diff;

    if (argc < 3) {
        printf("usage: %s [n] [asc/desc/rand]\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    n = atoi(argv[1]);
    array = (int*)malloc(sizeof(int) * n);

    if (strcmp(argv[2], "asc") == 0) {
        for (i = 0; i < n; i++) {
            array[i] = i;
        }
    } else if (strcmp(argv[2], "desc") == 0) {
        for (i = 0; i < n; i++) {
            array[i] = n - i - 1;
        }
    } else if (strcmp(argv[2], "rand") == 0) {
        for (i = 0; i < n; i++) {
            array[i] = rand() % n;
        }
    }

    before = clock(); 
    quicksort(array, n);
    after = clock(); 
    diff = (double)(after - before) / (CLOCKS_PER_SEC);

    for (i = 0; i < n; i++) {
        if (i > 0 && array[i-1] > array[i]) {
            printf("erroneous sorting at index %d/%d\n", i-1, i);
            exit(EXIT_FAILURE);
        }
    }

    printf("duration: %5.2f seconds\n", diff);

    return 0;
}

// quicksort: sort v[0]..v[n-1] into increasing order
void quicksort(int v[], int n)
{
    int i, last;

    // an array of 1 or less elements is sorted
    if (n <= 1) {
        return;
    }

    // random pivot element moved to beginning
    // swap(v, 0, rand() % n); 

    // take pivot element from the end
    // swap(v, 0, n - 1); 

    // take pivot element from the middle
    swap(v, 0, n / 2);

    last = 0;
    for (i = 1; i < n; i++) {
        if (v[i] < v[0]) {
            swap(v, ++last, i);
        }
    }

    // move pivot element to the boundary established
    swap(v, 0, last);

    // sort lower and upper part recursively
    quicksort(v, last);
    quicksort(v + last + 1, n - last - 1);
}

// swap: interchange v[i] and v[j]
void swap(int v[], int i, int j)
{
    int temp;

    temp = v[i];
    v[i] = v[j];
    v[j] = temp;
}
