typedef struct Nameval Nameval;

struct Nameval {
    char    *name;
    int     value;
    Nameval *next;      /* in chain */
};

/* lookup: find name in symtab, with optional create */
Nameval *lookup(char *name, int create, int value);
