#include <stdio.h>
#include <stdlib.h>

#define N_ELEMS(array) (sizeof(array) / sizeof(array[0]))

void quicksort(int[], int);
void swap(int[], int, int);

int main()
{
    int numbers[] = {6, 3, 7, 1, 9, 8, 0, 4, 5, 2};

    for (int i = 0; i < N_ELEMS(numbers); i++) {
        printf("%d ", numbers[i]);
    }
    putchar('\n');

    quicksort(numbers, N_ELEMS(numbers));

    for (int i = 0; i < N_ELEMS(numbers); i++) {
        printf("%d ", numbers[i]);
    }
    putchar('\n');

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
    swap(v, 0, rand() % n); 

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
