#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "tree.h"

#define STRLEN 20
#define N_CALLS 5000000

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

void printnv(Nameval *node, char *fmt)
{
	printf(fmt, node->name, node->value);
}

double benchmark_lookup(Nameval *tree,
                        Nameval *(*lookup_fn)(Nameval*, char*),
                        int n_calls)
{
	char *name;
	clock_t before;
	double elapsed;
	Nameval *result;
	int i;

	name = randstr(STRLEN);

	before = clock();
	for (i = 0; i < n_calls; i++) {
		result = (*lookup_fn)(tree, name);
	}
	elapsed = clock() - before;

	// activate for debugging
	/*
	if (result) {
		printf("found: %s = %d\n", result->name, result->value);
	} else {
		printf("name %s not found\n", name);
	}
	*/

	return elapsed / CLOCKS_PER_SEC;
}

int main(int argc, char *argv[])
{
	Nameval *tree;
	int n, i;
	double duration;

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

	tree = NULL;
	for (i = 0; i < n; i++) {
		tree = insert(tree, create(randstr(STRLEN), rand() % n));
	}

	// activate for debugging
	// applyinorder(tree, printnv, "%s: %d\n");

	duration = benchmark_lookup(tree, lookup, N_CALLS);
	printf("recursive: %.3fs for %d calls\n", duration, N_CALLS);
	duration = benchmark_lookup(tree, nrlookup, N_CALLS);
	printf("iterative: %.3fs for %d calls\n", duration, N_CALLS);

	return 0;
}
