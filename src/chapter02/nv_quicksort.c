#include "tree.h"

// swap: interchange v[i] and v[j]
void swap(Nameval *nv[], int i, int j)
{
    Nameval *temp;

    temp = nv[i];
    nv[i] = nv[j];
    nv[j] = temp;
}

// quicksort: sort v[0]..v[n-1] into increasing order
void quicksort(Nameval *nv[], int n)
{
    int i, last;

    // an array of 1 or less elements is sorted
    if (n <= 1) {
        return;
    }

    // random pivot element moved to beginning
    swap(nv, 0, rand() % n); 

    last = 0;
    for (i = 1; i < n; i++) {
        if (strcmp(nv[i]->name, nv[0]->name) < 0) {
            swap(nv, ++last, i);
        }
    }

    // move pivot element to the boundary established
    swap(nv, 0, last);

    // sort lower and upper part recursively
    quicksort(nv, last);
    quicksort(nv + last + 1, n - last - 1);
}
