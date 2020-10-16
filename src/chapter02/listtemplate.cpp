#include <iostream>

using namespace std;

template<typename T>
class Item {
    private:
        T value;
        Item<T> *next;
    public:
        Item<T>(T newValue)
        {
            value = newValue;
            next = 0;
        }
        T getValue()
        {
            return value;
        }
        Item<T> *getNext()
        {
            return next;
        }
        void setNext(Item<T> *newNext)
        {
            next = newNext;
        }
};

template<typename T>
class List {
    private:
        Item<T> *head;
        int n;
    public:
        List(T value)
        {
            Item<T> *item;
            item = new Item<T>(value);
            head = item;
            n = 1;
        }
        Item<T> *getHead()
        {
            return head;
        }
        void append(T value)
        {
            Item<T> *new_item, *tmp;

            new_item = new Item<T>(value);
            for (tmp = head; tmp != NULL; tmp = tmp->getNext()) {
                if (tmp->getNext() == NULL) {
                    tmp->setNext(new_item);
                    n++;
                    return;
                }
            }
        }
        ~List() {
            Item<T> *tmp, *last;

            last = NULL;
            for (tmp = head; tmp != NULL; tmp = tmp->getNext()) {
                if (last != NULL) {
                    delete last;
                }
                last = tmp;
            }
            if (last != NULL) {
                delete last;
            }
        }
        void each(void (*func)(Item<T> *item)) {
            Item<T> *tmp;

            for (tmp = head; tmp != NULL; tmp = tmp->getNext()) {
                func(tmp);
            }
        }
        int size() {
            return n;
        }
        Item<T> *get(int i) {
            Item<T> *item = NULL;
            
            if (i < 0 || i >= n) {
                return NULL;
            }

            for (item = head; item != NULL; item = item->getNext()) {
                if (i == 0) {
                    return item;
                }
                i--;
            }

            return NULL;
        }
};

template<typename T>
void print(Item<T> *item)
{
    cout << (*item).getValue() << '\n';
}

#ifndef _TESTING
int main()
{
    List<int> *numbers;
    numbers = new List<int>(1);

    numbers->append(2);
    numbers->append(3);
    numbers->append(4);

    numbers->each(print);

    cout << numbers->size() << " numbers\n";
    cout << "first number: " << (*numbers).get(0)->getValue() << '\n';
    cout << "second number: " << (*numbers).get(1)->getValue() << '\n';
    cout << "third number: " << (*numbers).get(2)->getValue() << '\n';
    cout << "fourth number: " << (*numbers).get(3)->getValue() << '\n';

    delete numbers;
}
#endif
