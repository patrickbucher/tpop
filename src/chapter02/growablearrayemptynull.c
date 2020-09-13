#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct Nameval Nameval;
struct Nameval {
    char    *name;
    int     value;
};
Nameval empty = {NULL, 0};

struct NVtab {
    int     nval;       /* current number of values */
    int     max;        /* allocated number of values */
    Nameval *nameval;   /* array of name-value pairs */
} nvtab;

enum { NVINIT = 1, NVGROW = 2 };

/* addname: add new name and value to nvtag */
int addname(Nameval newname)
{
    Nameval *nvp;
    int i;

    if (nvtab.nameval == NULL) { /* first time */
        nvtab.nameval = (Nameval *) malloc(NVINIT * sizeof(Nameval));
        if (nvtab.nameval == NULL) {
            return -1;
        }
        nvtab.max = NVINIT;
        nvtab.nval = 0;
    } else if (nvtab.nval >= nvtab.max) { /* grow */
        nvp = (Nameval *) realloc(nvtab.nameval,
                (NVGROW*nvtab.max) * sizeof(Nameval));
        if (nvp == NULL) {
            return -1;
        }
        nvtab.max *= NVGROW;
        nvtab.nameval = nvp;
    }
    for (i = 0; i < nvtab.nval; i++) { /* find gap to insert */
        if (nvtab.nameval[i].name == NULL) {
            break;
        }
    }
    nvtab.nameval[i] = newname;
    return nvtab.nval++;
}

/* delname: remove first matching nameval from nvtab */
int delname(char *name)
{
    int i;

    for (i = 0; i < nvtab.nval; i++) {
        if (strcmp(nvtab.nameval[i].name, name) == 0) {
            nvtab.nameval[i].name = NULL;
            nvtab.nval--;
            return 1;
        }
    }
    return 0;
}

void output()
{
    int i;

    for (i = 0; i < nvtab.nval; i++) {
        printf("%d: %s\n", nvtab.nameval[i].value, nvtab.nameval[i].name);
    }
    putchar('\n');
}

int main()
{
    Nameval a = {"Alice", 1};
    Nameval b = {"Bob", 2};
    Nameval c = {"Cindy", 3};
    Nameval d = {"Danny", 4};
    Nameval e = {"Elfie", 5};
    Nameval f = {"Freddie", 6};
    Nameval g = {"Georgina", 7};
    Nameval h = {"Hubert", 8};

    addname(a);
    addname(b);
    addname(c);
    addname(d);
    addname(e);

    output();

    delname("Cindy");
    addname(f);
    addname(g);

    output();

    delname("Alice");
    addname(h);

    output();
}
