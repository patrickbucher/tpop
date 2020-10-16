#include <assert.h>

#define _TESTING
#include "listtemplate.cpp"

int printed = 0;

template<typename T>
void spy_print(Item<T> *item)
{
	printed++;
}

int main()
{
	List<int> *numbers = new List<int>(100);
	assert(numbers != NULL);
	assert(numbers->size() == 1);
	assert(numbers->get(0) != NULL);
	assert(numbers->get(0)->getValue() == 100);

	numbers->append(200);
	assert(numbers->size() == 2);
	assert(numbers->get(0)->getValue() == 100);
	assert(numbers->get(1)->getValue() == 200);

	numbers->append(300);
	assert(numbers->size() == 3);
	assert(numbers->get(0)->getValue() == 100);
	assert(numbers->get(1)->getValue() == 200);
	assert(numbers->get(2)->getValue() == 300);

	assert(printed == 0);
	numbers->each(spy_print);
	assert(printed == 3);

	delete numbers;

	cout << "ok\n";
}
