# Chapter 1

> The principles of programming style are based on common sense guided by
> experience, not on arbitrary rules and prescriptions. (p. 2)

A good name indicates what _role_ a constant or variable plays in a program. (p. 2)

## Names

A good name is informative, concise, memorable, and pronouncable, if possible. (p. 3)

> The broader the scope of a variable, the more information should be conveyed
> by its name. (p. 3)

> Programmers are often encouraged to use long variable names regardless of
> context. That is a mistake: clarity is often achieved through brevity. (p. 3)

> Give related things related names that show their relationship and highlight
> their difference. (p. 4)

### Exercise 1-1

Comment on the choice of names and values in the following code.

    #define TRUE 0
    #define FALSE 1

    if ((ch = getchar()) == EOF)
        not_eof = FALSE;

Answer:

Values for `true` and `false` are commonly used the other way around: 0 is
`false`, 1 (or any other value than 0) is `true`. In many programming language,
conditions evaluating to the value 0 are `false`. So the choice above is not
only uncommon, but also dangerous. For example in C, the block for the
conditional `if (TRUE)` would never be executed.

The use of `ch` is ok in this context.

The line thereafter uses double negation, which is hard to read. Writing
`is_eof = TRUE` would be easier to understand.

### Exercise 1-2

Improve this function:

    int smaller(char *s, char *t) {
        if (strcmp(s, t) < 1)
            return 1;
        else
            return 0;
        }
    }

Answer:

    int smaller(char *s, char *t) {
        int comparison = strcmp(s, t);
        if (comparison < 0) {
            return 0;
        } else if (comparison > 0) {
            return 1;
        } else {
            return -1;
        }
    }

The discriminator value of 1 in the original implementation is wrong. The
boundary is zero.

### Exercise 1-3

Read this code aloud:

    if ((falloc(SMRHSHSCRTCH, S_IFEXT|0644, MAXPRODDHSH)) < 0)
        ...

Answer:

if falloc smerehashscratch, sifext or zero six four four, maxprod d hash is
smaller than zero

## Expressions and Statements

Bitwise operators have a very low precedence; parentheses are often needed. (p. 7)

### Exercise 1-4

Improve each of these fragments:

    // 1.
    if ( !(c == 'y' || c == 'Y') )
        return;

    // 2.
    length = (length < BUFSIZE) ? length : BUFSIZE;

    // 3.
    flag = flag ? 0 : 1;

    // 4.
    quote = (*line == '"') ? 1 : 0;

    // 5.
    if (val & 1)
        bit = 1;
    else
        bit = 0;

Answer:

    // 1.
    if (c != 'y' && c != 'Y')
        return;

    // 2.
    if (length >= BUFSIZE)
        length = BUFSIZE;

    // 3.
    if (flag)
        flag = 0;
    else
        flag = 1;

    // 4.
    quote = (*line == '"')

    // 5.
    bit = val & 1;

### Exercise 1-5

What is wrong with this excerpt?

    int read(int *ip) {
        scanf("%d", ip);
        return *ip;
    }

    insert(&graph[vert], read(&val), read(&ch));

Answer:

The position of the two values being read in the argument list of insert depend
on the order in which the two read function calls are executed, which is not
necessarily from the left to the right.

### Exercise 1-6

List all the different outputs this could produce with various orders of
evaluation:

    n = 1;
    printf("%d %d\n", n++, n++);

Try it on as many compilers as you can, to see what happens in practice.

Answer:

    1 1 (evaluate first, increment after)
    2 2 (increment first, evaluate after)
    1 2 (a mix thereof)
    2 1 (ditto)

GCC 10.2.0:

    2 1

TCC 0.9.27:

    1 2

CLANG 10.0.1 (Warning: "multiple unsequenced modifications to 'n'"):

    1 2

## Consistency and Idioms

> Buf if the same computation is done the same way every time it appears, any
> variation suggests a genuine difference, one worth noting. (p. 10)

When editing an existing code base, adapt to its style. The consistency within
a single code base is more important than the programmer's consistency over
different code bases. (p. 11)

Handle a multitude of `if`/`else` checks as a sequence of `else if` checks.
Deeply nested code is often hard to understand, for it "requires us to maintain
a mental pushdown stack of what tests wre made". Reacting to error cases first
leaves the code to be executed for the positive path in the final `else` block.
"Each time you make a test, do something." (p. 15)

### Exercise 1-7

Rewrite these C/C++ excerpts more clearly:

    // 1.
    if (istty(stdin))  ;
    else if (istty(stdout))  ;
        else if (istty(stderr))  ;
            else return(0);

    // 2.
    if (retval != SUCCESS)
    {
        return (retval);
    }
    /* All went well! */
    return SUCCESS;

    // 3.
    for (k = 0; k++ < 5; x += dx)
        scanf("%lf", &dx);

Answer:

    // 1.
    if (!istty(stdin) && !istty(stdout) && !istty(stderr) {
        return 0;
    }

    // 2.
    return retval;

    // 3.
    for (k = 0; k < 5; k++) {
        scanf("%lf", &dx);
        x += dx;
    }

### Exercise 1-8

Identify the errors in this Java fragment and repair it by rewriting with an
idiomatic loop:

    int count = 0;
    while (count < total) {
        count++;
        if (this.getName(count) == nametable.userName()) {
            return (true);
        }
    }

Answer:

    for (int count = 0; count < total; count++) {
        if (this.getName(count) == nametable.userName()) {
            return true;
        }
    }
