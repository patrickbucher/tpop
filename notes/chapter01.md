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

**Answer**: Values for `true` and `false` are commonly used the other way
around: 0 is `false`, 1 (or any other value than 0) is `true`. In many
programming language, conditions evaluating to the value 0 are `false`. So the
choice above is not only uncommon, but also dangerous. For example in C, the
block for the conditional `if (TRUE)` would never be executed.

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

**Answer**:

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

**Answer**: if falloc smerehashscratch, sifext or zero six four four, maxprod d
hash is smaller than zero

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

**Answer**:

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

**Answer**: The position of the two values being read in the argument list of
insert depend on the order in which the two read function calls are executed,
which is not necessarily from the left to the right.

### Exercise 1-6

List all the different outputs this could produce with various orders of
evaluation:

    n = 1;
    printf("%d %d\n", n++, n++);

Try it on as many compilers as you can, to see what happens in practice.

**Answer**:

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

> But if the same computation is done the same way every time it appears, any
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

**Answer**:

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

**Answer**:

    for (int count = 0; count < total; count++) {
        if (this.getName(count) == nametable.userName()) {
            return true;
        }
    }

## Function Macros

The argument expression is evaluated once for every occurrence in the macro
body. Function macros should not be used with arguments that cause side
effects. (p. 18)

Here, the parameter `c` is evaluated twice in the macro body.

    #define isupper(c) ((c) >= 'A' && (c) <= 'Z')

Using the macro as follows reads in _two_ characters per iteration:

    while (isupper(c = getchar())) {
        // ...
    }

The macro is better used as follows:

    while ((c = getchar()) != EOF && isupper(c)) {
        // ...
    }

However, it is better to avoid function macros alltogether.

Macros are based on textual substitution. The macro

    #define square(x) (x) * (x)

invoked as

    1 / square(x)

results in

    1 / (x) * (x)

rather than the intended

    1 / ((x) * (x))

Therefore, the macro body and all occurrences parameters must be surrounded
with parentheses:

    #define square(x) ((x) * (x))

Again, it's better to avoid function macros, because they are hard to get
right, and only have a marginal benefit.

### Exercise 1-9

Identify the problems with this macro definition:

    #define ISDIGIT(c) ((c > '0') && (c <= '9')) ? 1 : 0

**Answer**: There are two classes of problems.

1. Double evaluation: Since the parameter `c` occurs twice in the macro body,
invoking the macro with an expression that has side effects will result in two
different values for `c`.
2. Operator precedence: If the parameter expression for `c` contains an
operator with a _lower_ precedence than `>`, `<=`, or the ternary operator `?
:`, the result of the macro probably won't be as intended.  Therefore, the
whole macro body and the two occurrences of `c` must be wrapped in parentheses.

This implementation solves the second problem, but not the first.

    #define ISDIGIT(c) ((((c) > '0') && ((c) <= '9')) ? 1 : 0)

The first problem could be solved by introducing a temporary variable:

    static char tmp;
    #define ISDIGIT(c) ((tmp = c) && (((tmp) > '0') && ((tmp) <= '9')) ? 1 : 0)

However, the variable `tmp` could cause unwanted side effects when multiple
threads are using the `ISDIGIT` macro. Again, it's better to avoid function
macros.

## Magic Numbers

Any number other than 0 or 1 is likely to be a magic number. (p. 19)

Magic numbers are often the result of a calculation, which no longer can be
understood if only the result is visible. For example, for an array with 50
elements, 49 is the topmost array index. An expression like `ARRAY_LENGTH - 1`
makes this obvious. (p. 20)

Define constants using the `const` keyword, if possible. In C, `const` values
cannot be used as array bounds, but one can use an `enum` instead. (p. 20/21)

The number 0 can be used in different ways. Use the following representations
of it to clarify the role of 0 in the respective context:

- null pointer: `(void*)0` or `NULL`
- null character: `'\0'`
- number zero: `0` or `0.0` (integer and floating point)

Sizes are best computed by the means the language offers. It's better to use
`sizeof(array[0])` than `sizeof(int)`, even if `array` is of type `int`; if the
type of `array` changes, the size still will be calculated correctly. (p. 22)

The length of an array in C is best computed as follows:

    sizeof(array) / sizeof(array[0])

Here, a macro can do what a function cannot (p. 22):

    #define NELEMS(array) (sizeof(array) / sizeof(array[0]))

### Exercise 1-10

How would you rewrite these definitions to minimize potential errors?

    #define FT2METER    0.3048
    #define METER2FT    3.28084
    #define MI2FT       5280.0
    #define MI2KM       1.609344
    #define SQMI2SQM    2.589988

**Answer**:

    const float foot_in_meters = 0.3048;
    const float meters_in_feet = 1 / foot_in_meters;
    const float miles_in_feet = 5280.0;
    const float miles_in_kilometers = 1.609344;
    const float square_miles_in_square_kilometers = 2.589988;

Some alternatives:

    const float meters_in_kilometer = 1000;
    const float miles_in_kilometers = miles_in_feet * foot_in_meters * meters_in_kilometer;
    const float square_miles_in_square_kilometers = miles_in_kilometers * miles_in_kilometers;

## Comments

> The best comments aid the understanding of a program by briefly pointing out
> salient details or by providing a larget-scale view of the proceedings. (p. 23)

Comments are a good way to document a data structure or function interface.
References to algorithms being implemented can also be helpful. (p. 24)

Heuristic: "When the comment outweighs the code, the code probably needs
fixing." (p. 25)

### Exercise 1-11

Comment on these comments.

First example:

    void dict::insert(string& w)
    // returns 1 if w in dictionary, otherwise returns 0

"if w in dictionary" reads like a state check, while the function name "insert"
rather reads like a function with a side effect. Either the function is not
named properly, or the comment sould read:

    // inserts w into the dictionary; returns 1 if that worked, and 0 otherwise

Second example:

    if (n > MAX || n % 2 > 0) // test for even number

It is true that `n % 2 > 0` is a condition related to an even number; but in
this case, the body of the `if` statement is only entered if `n` _not_ is an
even number. Furthermore, there is a second check for a upper boundary, which
is not mentioned in the comment.

`n % 2 != 0` is the more idiomatic way to express a "test for an _uneven_
number". The comment could be deleted then.

Third example:

    // Write a message
    // Add to line counter for each line written

    void write_message()
    {
        // increment line counter
        line_number = line_number + 1;
        fprintf(fout, "%d  %s\n%d  %s\n%d  %s\n",
            line_number, HEADER,
            line_number + 1, BODY,
            line_number + 2, TRAILER);
        // increment line counter
        line_number = line_number + 2;
    }

"Write a message" is already in the function name. The second comment line
could be clarified, so that the line number is increased by the number of lines
written.

The two comments "increment line counter" are superfluous. It would be
interesting to know why the increment is done in two lines, once by 1, and once
by 2. The more idiomatic `line_number += 3` after `fprintf` probably would have
done it, too.
