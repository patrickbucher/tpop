#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

#define _TESTING
#include "tree.h"
#include "treesort.c"
#include "nv_quicksort.c"

#define STRLEN 20

double benchmark_treesort(Nameval **nvs, int n);
double benchmark_quicksort(Nameval **nvs, int n);
double benchmark_libsort(Nameval **nvs, int n);

Nameval **create_test_data(int n);
Nameval **shallow_copy(Nameval **nvs, int n);
char *randstr(int len);

int main(int argc, char *argv[])
{
    Nameval **nvs1, **nvs2, **nvs3;
    int n;
    double duration_treesort, duration_quicksort, duration_libsort;

    if (argc < 2) {
        printf("usage: %s [n_items]\n", argv[0]);
        return 1;
    }

    n = atoi(argv[1]);
    if (n < 1) {
		puts("n_items must be a positive number");
		return 1;
    }
	srand(time(NULL));

    nvs1 = create_test_data(n);
    nvs2 = shallow_copy(nvs1, n);
    nvs3 = shallow_copy(nvs1, n);

    duration_treesort = benchmark_treesort(nvs1, n);
    duration_quicksort = benchmark_quicksort(nvs2, n);
    duration_libsort = benchmark_libsort(nvs3, n);

    printf("treesort:\t%.3f\n", duration_treesort);
    printf("quicksort:\t%.3f\n", duration_quicksort);
    printf("libsort:\t%.3f\n", duration_libsort);

    return 0;
}


Nameval **create_test_data(int n)
{
    Nameval **nvs, *nv;
    int i;

    nvs = (Nameval**)malloc(sizeof(Nameval*) * n);

    for (i = 0; i < n; i++) {
        nv = (Nameval*)malloc(sizeof(Nameval));
        nv->name = randstr(STRLEN);
        nv->value = rand() % n;
        nv->left = NULL;
        nv->right = NULL;
        nvs[i] = nv;
    }

    return nvs;
}

Nameval **shallow_copy(Nameval **nvs, int n)
{
    Nameval **cpy;
    int i;

    cpy = (Nameval**)malloc(sizeof(Nameval*) * n);

    for (i = 0; i < n; i++) {
        cpy[i] = nvs[i];
    }

    return cpy;
}

char *randstr(int len)
{
	char *str;
	int i;

	if (len < 1) {
		return NULL;
	}

	str = (char*)malloc(sizeof(char) * (len + 1));
	for (i = 0; i < len; i++) {
		str[i] = (char)(rand() % ('z' - 'a' + 1)) + 'a';
	}
	str[len] = '\0';

	return str;
}

double benchmark_treesort(Nameval **nvs, int n)
{
    clock_t before;

    before = clock();

    treesort(nvs, n);

    return (clock() - before) / CLOCKS_PER_SEC;
}

double benchmark_quicksort(Nameval **nvs, int n)
{
    clock_t before;

    before = clock();

    quicksort(nvs, n);

    return (clock() - before) / CLOCKS_PER_SEC;
}

int compare(const void *a, const void *b)
{
    return strcmp(((Nameval*)a)->name, ((Nameval*)b)->name);
}

double benchmark_libsort(Nameval **nvs, int n)
{
    clock_t before;

    before = clock();

    qsort(nvs, n, sizeof(Nameval*), compare);

    return (clock() - before) / CLOCKS_PER_SEC;
}
