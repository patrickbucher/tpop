# Algorithms and Data Structures

Only few programs require new data structures and algorithms to be invented.
Well-known and well-understood data structures, such as arrays, lists, maps,
and trees, and data structures derived thereof, are usually enough to solve a
problem. (p. 29)

## Searching

Sequential search is fast enough for small and medium size arrays. For large
arrays, binary search is much faster, but requires the underlying array to be
sorted. (p. 30/31) A linear search in `n` elements requires at most `n` steps,
a binary search only requires up to `log2 n` steps. The more items, the greater
the advantage of binary search. (p. 32)

## Sorting

If a large array is to be searched multiple times, it is profitable to first
sort the array, and then to perform binary instead of linear search on it. (p.
32)

When implementing quicksort, moving a random pivot element at the beginning of
the array, and back after the boundary has been established, makes the
calculation of indices easier. (p. 33)

Depending on the input, quicksort has a complexity of `n log 2 n` (best case)
up to `n^2` (worst case). (p. 34)

## Libraries

In order to use the generalized `qsort` function provided by the C Standard
Library, one must implement a comparison function of the following signature:

    int compare(const void *left, const void *right);

A negative value indicates that `left < right`, a positive value `left >
right`, and a value of zero `left == right`. (Which can remembered by
calculating `left - right`, which yields that exact result.)

Casting the `void` pointers to the proper type is the programmer's
responsibility (p. 35).

The `qsort` library function can be invoked as follows:

    char *strings[N];
    qsort(strings, N, sizeof(strings[0]), compare);

A comparison function like above can also be reused for the `bsearch` library
function, which offers a generalized implementation for a binary search (p.
36/37).

### Exercise 2-1

Quicksort is most naturally expressed recursively. Write it iteratively and
compare the two versions. (Hoare describes how hard it was to work out
quicksort iteratively, and how neatly it fell into place when he did it
recursively.)

Answer:

The basic idea is to put on a stack what otherwise would be on a call stack:
the function arguments that denote the partition boundaries.

    typedef struct {
        int *v;
        int n;
    } partition;


The process is repeated as long as there are items on the stack, and those
items denote array partitions of one or more elements.

See `iterqsort.c` in the `examples/chapter02` folder.

## A Java Quicksort

### Exercise 2-2

Our Java quicksort does a fair amount of type converrsion as items are cast
from their original type (like `Integer`) to `Object` and back again.
Experiment with a version of `Quicksort.sort` that uses the specific type being
sorted, to estimate what performance penalty is incurred by type conversions.

Answer:

Sorting 10 million random strings of the length 10 with the generic solution
yields the following timing:

    real    0m19.868s
    user    0m30.314s
    sys     0m0.427s

A version implemented only for strings (`quickstringsort.java`) with the same
workload yields the following timing:

    real    0m17.164s
    user    0m27.586s
    sys     0m0.477s

The difference is small, and might also be caused by the direct comparison, as
opposed to the comparison using an interface implementation. In practice, it
won't pay off to implement special versions.

## O-Notation

A `O(n^2)` algorithm may run faster for smaller input than a `O(n log n)`
algorithm. The expected behaviour of a algorithm is often better than the worst
case behaviour. (p. 40)

Examples of runtime complexity (p. 41):

| Notation     | Name        | Example                |
|--------------|-------------|------------------------|
| `O(1)`       | constant    | array index            |
| `O(log n)`   | logarithmic | binary search          |
| `O(n)`       | linear      | string comparison      |
| `O(n log n)` | n log n     | quicksort              |
| `O(n^2)`     | quadratic   | simple sorting methods |
| `O(n^3)`     | cubic       | matrix multiplication  |
| `O(2^n)`     | exponential | set partitioning       |

### Exercise 2-3

What are some input sequences that might cause a quicksort implementation to
display worst-case behaviour? Try to find some that provoke your library
version into running slowly. Automate the process so that you can specify and
perform a large number of experiments easily.

Answer:

The program `qsortbench.c` generates arrays of a specific size in ascending,
descending, or random order and sorts it. A random pivot element is selected.
These are the timings:

    $ ./qsortbench 50000000 asc
    duration:  8.23 seconds
    $ ./qsortbench 50000000 desc
    duration:  8.89 seconds
    $ ./qsortbench 50000000 rand
    duration: 13.94 seconds

The random array takes significantly longer than ascending and descending
ordered arrays to sort.

The situation looks much different if the last element is picked as the pivot
element. Here, the random array yields the most sensible pivot elements, and
runs considerably faster than the other two (notice that the array is now much
smaller):

    $ ./qsortbench 50000 asc
    duration:  8.71 seconds
    $ ./qsortbench 50000 desc
    duration:  5.50 seconds
    $ ./qsortbench 50000 rand
    duration:  0.01 seconds

If the pivot element is picked from the middle, the algorithm runs fast again
for all kinds of inputs:

    $ ./qsortbench 50000000 asc
    duration:  5.76 seconds
    $ ./qsortbench 50000000 desc
    duration:  6.21 seconds
    $ ./qsortbench 50000000 rand
    duration: 13.59 seconds

Here, the ordered arrays are sorted the fastest.

### Exercise 2-4

Design and implement an algorithm that will sort an array of `n` integers as
slowly as possible. You have to play fair: the algorithm must make progress and
eventually terminate, and the implementation must not cheat with tricks like
time-wasting loops. What is the complexity of your algorithm as a function of
`n`?

Answer: A very inefficient implementation would be to shuffle the array until
it is sorted. Both shuffling and comparison can be implemented with `O(n)`
complexity. In the worst case, it will take all permutations of the array to be
built until a sorted version is found. (Finding the permutations is a more
systematic approach and will terminate eventually; shuffling randomly perhaps
does not qualify as an algorithm, because it might never finish.) An array of
`n` elements has `!n` permutations. This is even worse than `O(2^n)`:

| n | n!  | 2^n |
|---|----:|----:|
| 1 |   1 |   2 |
| 2 |   2 |   4 |
| 3 |   6 |   8 |
| 4 |  24 |  16 |
| 5 | 120 |  32 |

TODO: implementation
