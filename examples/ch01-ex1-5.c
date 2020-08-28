#include <stdio.h>

void debug(int a, int b)
{
    printf("first: %d, second: %d\n", a, b);
}

int read(int *ip) {
    scanf("%d", ip);
    return *ip;
}

int main()
{
    int val, ch;
    debug(read(&val), read(&ch));
}
