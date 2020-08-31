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

    TODO

## A Java Quicksort

### Exercise 2-2

Our Java quicksort does a fair amount of type converrsion as items are cast
from their original type (like `Integer`) to `Object` and back again.
Experiment with a version of `Quicksort.sort` that uses the specific type being
sorted, to estimate what performance penalty is incurred by type conversions.

## O-Notation

TODO: p. 40 ff.
