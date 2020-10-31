#include <assert.h>
#include <stdio.h>

#include "tree.h"

void printnv(Nameval *node, char *fmt)
{
	printf(fmt, node->name, node->value);
}

void add_points(Nameval *node, int *sum)
{
    *sum += node->value;
}

int main()
{
	Nameval *tree, *node;
	Nameval *ham, *bot, *ver, *ric, *per, *nor, *alb;
    int points;

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

    assert(lookup(tree, "Hamilton")->value == 230);
    assert(lookup(tree, "Bottas")->value == 161);
    assert(lookup(tree, "Verstappen")->value == 147);
    assert(lookup(tree, "Ricciardo")->value == 78);
    assert(lookup(tree, "Perez")->value == 68);
    assert(lookup(tree, "Norris")->value == 65);
    assert(lookup(tree, "Albon")->value == 64);

    assert(nrlookup(tree, "Hamilton")->value == 230);
    assert(nrlookup(tree, "Bottas")->value == 161);
    assert(nrlookup(tree, "Verstappen")->value == 147);
    assert(nrlookup(tree, "Ricciardo")->value == 78);
    assert(nrlookup(tree, "Perez")->value == 68);
    assert(nrlookup(tree, "Norris")->value == 65);
    assert(nrlookup(tree, "Albon")->value == 64);

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

    points = 0;
    applyinorder(tree, add_points, &points);
    assert(points == 230 + 161 + 147 + 78 + 68 + 65 + 64);

    points = 0;
    applypostorder(tree, add_points, &points);
    assert(points == 230 + 161 + 147 + 78 + 68 + 65 + 64);

	return 0;
}
