typedef struct Nameval Nameval;

struct Nameval {
    char    *name;
    int     value;
    Nameval *left;
    Nameval *right;
};

/* create: initialize Nameval with name and value, return it */
Nameval *create(char *name, int value);

/* insert: insert newp in treep, return treep */
Nameval *insert(Nameval *treep, Nameval *newp);

/* lookup: look up name in tree treep */
Nameval *lookup(Nameval *treep, char *name);

/* nrlookup: non-recursively look up name in tree treep */
Nameval *nrlookup(Nameval *treep, char *name);

/* applyinorder: inorder application of fn to treep */
void applyinorder(Nameval *treep,
                  void (*fn)(Nameval*, char*),
                  void *arg);

/* applypostorder: postorder application of fn to treep */
void applypostorder(Nameval *treep,
                    void (*fn)(Nameval*, char*),
                    void *arg);
