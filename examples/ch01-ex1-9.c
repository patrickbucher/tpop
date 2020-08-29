#include <stdio.h>

static char tmp;
#define ISDIGIT(c) ((tmp = c) && (((tmp) > '0') && ((tmp) <= '9')) ? 1 : 0)

int main()
{
    char c;
    while (ISDIGIT(c = getchar())) {
        putchar(c);
    }
}
