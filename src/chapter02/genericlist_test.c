#include <assert.h>

#define _TESTING
#include "genericlist.c"

int executed = 0;

void spy_print(Item *item)
{
	executed++;
}

int main()
{
	List *scores;
	float first, second, third;

	first = 1.11;
	scores = new_list((void*)&first);
	assert(scores != NULL);
	assert(size(scores) == 1);
	assert(*(float*)get(scores, 0) == first);

	second = 2.22;
	append(scores, (void*)&second);
	assert(size(scores) == 2);
	assert(*(float*)get(scores, 0) == first);
	assert(*(float*)get(scores, 1) == second);

	third = 3.33;
	append(scores, (void*)&third);
	assert(size(scores) == 3);
	assert(*(float*)get(scores, 0) == first);
	assert(*(float*)get(scores, 1) == second);
	assert(*(float*)get(scores, 2) == third);

	assert(executed == 0);
	each(scores, spy_print);
	assert(executed == 3);

	puts("ok");

	return 0;
}
