typedef struct Nameval Nameval;
struct Nameval {
    char    *name;
    int     value;
    Nameval *next; /* in list */
};

Nameval *newitem(char *name, int value);
Nameval *addfront(Nameval *listp, Nameval *newp);
Nameval *addend(Nameval *listp, Nameval *newp);
Nameval *lookup(Nameval *listp, char *name);
void apply(Nameval *listp, void (*fn)(Nameval*, void*), void *arg);
void printnv(Nameval *p, void *arg);
void inccounter(Nameval *p,void *arg);
void freeall(Nameval *listp);
Nameval *delitem(Nameval *listp, char *name);
Nameval *copy(Nameval *src);
Nameval *copyitem(Nameval *orig);

void *emalloc(size_t size);
void eprintf(char *fmt, char *arg);
