#include <stdio.h>

#include "tree.h"

void printnv(Nameval *node, char *fmt)
{
	printf(fmt, node->name, node->value);
}

int main()
{
	Nameval *tree, *node;
	Nameval *ham, *bot, *ver, *ric, *per, *nor, *alb;

	ham = create("Hamilton", 230);
	bot = create("Bottas", 161);
	ver = create("Verstappen", 147);
	ric = create("Ricciardo", 78);
	per = create("Perez", 68);
	nor = create("Norris", 65);
	alb = create("Albon", 64);

	tree = NULL;
	tree = insert(tree, ham);
	tree = insert(tree, bot);
	tree = insert(tree, ver);
	tree = insert(tree, ric);
	tree = insert(tree, per);
	tree = insert(tree, nor);
	tree = insert(tree, alb);

	printf("%s: %d\n", tree->name, tree->value);

	node = NULL;
	node = lookup(tree, "Perez");
	printf("%s: %d\n", node->name, node->value);

	node = nrlookup(tree, "Bottas");
	printf("%s: %d\n", node->name, node->value);

	puts("Apply in-order");
	applyinorder(tree, printnv, "%s: %d\n");

	puts("Apply post-order");
	applypostorder(tree, printnv, "%s: %d\n");

	return 0;
}
