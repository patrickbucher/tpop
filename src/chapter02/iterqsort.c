#include <stdio.h>
#include <stdlib.h>

#define N_ELEMS(array) (sizeof(array) / sizeof(array[0]))

void quicksort(int[], int);
void swap(int[], int, int);

#define LENGTH 1000
#define MAX 10000

int main()
{
    int numbers[LENGTH];

    for (int i = 0; i < N_ELEMS(numbers); i++) {
        numbers[i] = rand() % MAX;
        printf("%d ", numbers[i]);
    }
    putchar('\n');

    quicksort(numbers, N_ELEMS(numbers));

    int last = -1;
    for (int i = 0; i < N_ELEMS(numbers); i++) {
        if (numbers[i] < last) {
            printf("error detected: numbers[%d-1] < numbers[%d]\n", i-1, i);
            exit(-1);
        }
        printf("%d ", numbers[i]);
        last = numbers[i];
    }
    putchar('\n');

    return 0;
}

typedef struct {
    int *v;
    int n;
} partition;

// quicksort: sort v[0]..v[n-1] into increasing order
void quicksort(int v[], int n)
{
    partition *stack = (partition*)malloc(sizeof(partition) * n);
    int stackp = 0;

    partition whole;
    whole.v = v;
    whole.n = n;
    stack[stackp++] = whole;

    while (stackp > 0) {

        int i, last;

        partition current = stack[--stackp];
        v = current.v;
        n = current.n;

        // an array of 1 or less elements is sorted
        if (n <= 1) {
            continue;
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

        // sort lower and upper part in the next run
        partition left;
        partition right;

        left.v = v;
        left.n = last;

        right.v = v + last + 1;
        right.n = n - last - 1;

        stack[stackp++] = left;
        stack[stackp++] = right;
    }
}

// swap: interchange v[i] and v[j]
void swap(int v[], int i, int j)
{
    int temp;

    temp = v[i];
    v[i] = v[j];
    v[j] = temp;
}
