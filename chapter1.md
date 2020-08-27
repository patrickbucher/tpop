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
