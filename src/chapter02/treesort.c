#include <stdio.h>

#include "tree.h"

void store_inplace(Nameval *tree, Nameval *nvs[], int *i)
{
	if (tree == NULL) {
		return;
	}
	store_inplace(tree->left, nvs, i);
	nvs[*i] = tree;
	*i += + 1;
	store_inplace(tree->right, nvs, i);
}

/* treesort: sorts the given n items by name in-place using a binary tree*/
void treesort(Nameval *nvs[], int n)
{
	Nameval *tree;
	int i;

	tree = NULL;
	for (i = 0; i < n; i++) {
		tree = insert(tree, nvs[i]);
	}

	i = 0;
	store_inplace(tree, nvs, &i);
}

#ifndef _TESTING
int main()
{
	Nameval *nvs[21];
	int i, n;

	i = 0;
	n = 21;

	nvs[i++] = create("Hamilton", 256);
	nvs[i++] = create("Bottas", 179);
	nvs[i++] = create("Verstappen", 162);
	nvs[i++] = create("Ricciardo", 80);
	nvs[i++] = create("Leclerc", 75);
	nvs[i++] = create("Perez", 74);
	nvs[i++] = create("Norris", 65);
	nvs[i++] = create("Albon", 64);
	nvs[i++] = create("Gasly", 63);
	nvs[i++] = create("Sainz", 59);
	nvs[i++] = create("Stroll", 57);
	nvs[i++] = create("Ocon", 40);
	nvs[i++] = create("Vettel", 18);
	nvs[i++] = create("Kvyat", 14);
	nvs[i++] = create("Hulkenberg", 10);
	nvs[i++] = create("Giovinazzi", 3);
	nvs[i++] = create("Raikkonen", 2);
	nvs[i++] = create("Grosjean", 2);
	nvs[i++] = create("Magnussen", 1);
	nvs[i++] = create("Latifi", 0);
	nvs[i++] = create("Russell", 0);

	treesort(nvs, 21);

	for (i = 0; i < 21; i++) {
		printf("%-16s %3d\n", nvs[i]->name, nvs[i]->value);
	}

	return 0;
}
#endif
