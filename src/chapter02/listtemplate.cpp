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
    public:
        List(T value)
        {
            Item<T> *item;
            item = new Item<T>(value);
            head = item;
        }
        Item<T> *getHead()
        {
            return head;
        }
        void append(T value)
        {
            Item<T> *new_item, *tmp;

            new_item = new Item<T>(value);
            for (tmp = head; tmp != NULL; tmp = (*tmp).getNext()) {
                if ((*tmp).getNext() == NULL) {
                    (*tmp).setNext(new_item);
                    return;
                }
            }
        }
        ~List() {
            Item<T> *tmp, *last;

            last = NULL;
            for (tmp = head; tmp != NULL; tmp = (*tmp).getNext()) {
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

            for (tmp = head; tmp != NULL; tmp = (*tmp).getNext()) {
                func(tmp);
            }
        }
};

template<typename T>
void print(Item<T> *item)
{
    cout << (*item).getValue() << '\n';
}

int main()
{
    List<int> *numbers;
    numbers = new List<int>(1);

    (*numbers).append(2);
    (*numbers).append(3);
    (*numbers).append(4);

    (*numbers).each(print);
}
