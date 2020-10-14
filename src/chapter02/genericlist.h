typedef struct Item Item;
struct Item {
    void *value;
    Item *next;
};

typedef struct List List;
struct List {
    Item *head;    
};

List *new_list(void *value);
void del_list(List *list);
void append(List *list, void *value);
void each(List *list, void (*func)(Item*));
int size(List *list);
void *get(List *list, int i);
