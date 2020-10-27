$# Algorithms and Data Structures

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

**Answer**: The basic idea is to put on a stack what otherwise would be on a
call stack: the function arguments that denote the partition boundaries.

    typedef struct {
        int *v;
        int n;
    } partition;


The process is repeated as long as there are items on the stack, and those
items denote array partitions of one or more elements.

See `iterqsort.c` in the `src/chapter02` folder.

## A Java Quicksort

### Exercise 2-2

Our Java quicksort does a fair amount of type converrsion as items are cast
from their original type (like `Integer`) to `Object` and back again.
Experiment with a version of `Quicksort.sort` that uses the specific type being
sorted, to estimate what performance penalty is incurred by type conversions.

**Answer**: Sorting 10 million random strings of the length 10 with the generic
solution yields the following timing:

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

**Answer**: The program `qsortbench.c` generates arrays of a specific size in
ascending, descending, or random order and sorts it. A random pivot element is
selected. These are the timings:

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

**Answer**: A very inefficient implementation would be to shuffle the array
until it is sorted. Both shuffling and comparison can be implemented with
`O(n)` complexity. In the worst case, it will take all permutations of the
array to be built until a sorted version is found. (Finding the permutations is
a more systematic approach and will terminate eventually; shuffling randomly
perhaps does not qualify as an algorithm, because it might never finish.) An
array of `n` elements has `!n` permutations. This is even worse than `O(2^n)`:

| n | n!  | 2^n |
|---|----:|----:|
| 1 |   1 |   2 |
| 2 |   2 |   4 |
| 3 |   6 |   8 |
| 4 |  24 |  16 |
| 5 | 120 |  32 |

The `src` folder contains `permutationsort.c`, which sorts an array of ten
integers using permutation sort. The program requires more than 500 megabytes
and takes more than a second to sort the array of ten elements.

Eleven elements take more than 14 seconds and require roughly 4 gigabytes of
memory.

The algorithm can be optimized to stop as soon as an ordered permutation is
found, rather than building all permutations. (But optimization is not the
point here.)

## Growing Arrays

Inserting into a fixed-size, sorted array is an `O(n^2)` operation. (p. 41)

An array should be resized in chunks for efficiency. (p. 42)

The C standard library has two functions for copying memory parts: `memcpy` and
`memmove`. `memcpy` is faster, but might overwrite memory if source and
destination overlap. `memmove` is slower but safer. (p. 43)

### Exercise 2-5

In the code above, `delname` doesn't call realloc to return the memory freed by
the deletion. Is this worthwile? How would you decide whether to do so?

**Answer**: Deleting an array element can only shrink the array by one element at a
time, whereas adding elements might grow the array by its total size. It is
likely that a delete operation is followed by another add operation (otherwise,
the array would just be deleted). Thus, the gained space will just be
reallocated later on. This won't save anything, but cause even more memory
operations. It might be sensible to shrink an array after many elements have
been removed, say, if the number of items is less than half of the array's
capacity (symmetric approach).

### Exercise 2-6

Implement the necessary changes to `addname` and `delname` to delete items by
marking deleted items as unused. How isolated is the rest of the program from
this change?

**Answer**: An empty `Nameval` instance (`Nameval empty = {NULL, 0}`) can be used
to mark positions as empty. In `delname`, the part after the deleted entry no
longer needs to be moved in memory. However, a loop to output all values needs
to skip the `empty` value, which is best detected by comparing the `name` field
to `NULL`. In `addname`, an additional loop has to be introduced, which first
looks for empty spots in the range `0 < i < nvtab.nval`. After the loop, `i` is
the index of an empty spot in the array (either referring to a gap, or to the
beginning of the free area). The program is implemented in
`src/chapter02/growablearrayemptynull.c`.

## Lists

Lists can be rearranged by changing some pointers. No big memory chunks need to
be moved, as for arrays. Arrays have faster random lookup, but lists are faster
when it comes to adding and removing items. (p. 45)

In C, rather an _element_ type than a _list_ type needs to be implemented
first. Lists are usually constructed dynamically; not statically, as it is
common with arrays. (p. 45)

Adding elements at the beginning of a list is very cheap, but requires to
reassign the variable pointing to the beginning of the list. Adding elements at
the end of a list either requires traversal through the hole list (`O(n)`) or
maintaining a second pointer to the end of the list. (p. 46)

### Exercise 2-7

Implement some of the other list operators: copy, merge, split, insert before
or after a specific item. How do the two insertion operations differ in
difficulty? How much can you use the routine we've written, and how much must
you create yourself?

**Answer**: The operations have been implemented as the following functions
(see `src/chapter02/list.h`):

    Nameval *copy(Nameval *src);
    Nameval *copyitem(Nameval *orig);
    Nameval *merge(Nameval *first, Nameval *second);
    void split(Nameval *list, char *name, Nameval **first, Nameval **second);
    Nameval *insert_before(Nameval *add, Nameval *list, char *before);
    void *insert_after(Nameval *add, Nameval *list, char *after);

With `copyitem` being a utility function for the `copy` operation.

The `insert_before` function is more difficult to implement. It requires to
maintain a pointer to the list item visited previously, so that the item to be
inserted can be attached to it. It's also possible that the first list item is
replaced by the item to be added. Thus, `insert_before` returns a pointer to
the first item after the insertion operation is needed. In contrast,
`insert_after` cannot change the first item, and therefore doesn't return a
pointer. Its implementation doesn't require to maintain a pointer to the item
previously visited.

The `copy` function made use of the existing `addend` function, but also
required the addition of the `copyitem` function. Both functions were re-used
to write the `merge` function. `addend` was again used for the `split`
function. Code re-use helped a lot in this exercise.

### Exercise 2-8

Write recursive and iterative versions of `reverse`, which reverses a list. Do
not create new list items; re-use the existing ones.

**Answer**: The recursive function was implemented as `reverse_rec`, and
requires an internal function `reverse_rec_internally`, which also keeps track
of the new head (the old tail, that is). The iterative function was implemented
as `reverse_iter` and uses a stack to unwind the original list. The new list is
then rebuilt by taking from the stack.

A stack is a very helpful data structure when it comes to re-implementing
recursive functions iteratively. This is because recursion works like a stack.

### Exercise 2-9

Write a generic `List` type for C. The easiest way is to have each list item
hold a `void*` that points to the data. Do the same for C++ by defining a
template and for Java by defining a class that holds lists of type `Object`.
What are the strengths and weaknesses of the various languages for this job?

**Answer**: See the C implementation in `src/chapter02/genericlist.c` with
headers in `src/chapter02/genericlist.h`. Both a `List` and `Item` type have
been defined. Only a few operations have been implemented (create with
`new_list`, cleanup with `del_list`, add an item to the end with `append`, and
invoke a given function on every item using `each`).

The C++ implementation is in `src/chapter02/listtemplate.cpp`. It supports the
same operations as the C implementation, but uses a constructor and destructore
instead of the functions `new_list` and `del_list`. Both `List` and `Item` have
been implemented as classes.

The Java implementation in `src/chaptter02/GenericList.java` was done in
pre Java 1.5 fashion, i.e. with an `Object` instead of using generics. It
supports the same operations as the former two implementations.

The C implementation can store any type, but requires specific function
implementations for each type in order to use the `each` operation.

The C++ implementation provides a stronger abstraction than the C implementation
using thanks to classes. Memory is released using a destructor.

The Java implementation is similar to the C++ implementations, but doesn't make
use of generics. Providing a function for the `each` operation requires an
interface and an implementation. No memory management is required due to the
garbage collector.

### Exercise 2-10

Devise and implement a set of tests for verifying that the list routines you
write are correct. Chapter 6 discusses strategies for testing.

**Answer**: In order to verify the implemented list operations, two additonal
operations shall be added to all three implementations: `size()`, which returns
the number of elements in the list,  and `get()`, which returns the list element
at the given index.

The C implementation is tested by `genericlist_test.c`. A list of three float
items is created. The `size()` and `get()` operation are tested after the list
is created initially, and after each `append()` operation, respectively. A spy
is implemented to count the executions of the `each()` operation.

The test code directly includes the `.c` file. A `_TESTING` constant ist
defined, and the original `main()` function in `genericlist.c` is only
compiled, if `_TESTING` is _not_ set.

The C++ implementation is tested by `listtemplate_test.cpp`. It works a lot
like the test for the C implementation, but uses integers instead of floats.

The Java implementation is tested by `GenericListTest.java`. Here, strings are
used instead of numeric types. The spy for testing the `each()` operation has
been implemented as a class. It is more powerful than the two spies
aforementioned, because it stores the side effect in a buffer, which then is
tested for including all the values processed.

The tests can be run in `src/chapter02` by typing `make test`.

## Trees

In a _tree_, no node points to the root node. The leafs don't point to any other
node. All the other nodes are both pointed to and do point to other nodes
(possibly leafs).

In a _binary tree_, every node has a value and two pointers: left and right,
which are pointing to nodes with a lower (left) or higher (right) value,
respectively.

Operations that take time `O(n)` for lists or arrays only take time `O(log n)`
for trees, because the number of nodes to be visisted is reduced by the
pointers referring to lower/higher nodes.

In a _balanced tree_, each path from the root to a leaf has approximately the
same length, and thus, searching an item takes time `O(log n)`. If elements are
inserted in sorted order, all the nodes will be attached to the right pointer
like a linked list. This can be avoided in many cases by inserting items in
random order.

There are three ways of processing the tree's nodes:

- _pre-order_: The node is processed, the left branche is traversed, the right
  branch is traversed. (Rarely used)
- _in-order_: The left branch is traversed, the node is processed, the right
  branch is traversed.
    - This traversal processes the nodes in their sorted order.
    - Application: Output or storage in sorted order.
- _post-order_: The left branch is traversed, the right branch is traversed,
  the node is processed.
    - This traversal is used if the operation on the node depends on its subtrees.
    - Application: Computing the height of a tree, printing it graphically.

Trees are useful to represent the syntax of a program (_parse trees_):

    med = (min + max) / 2;

           =
         /   \
       med   /
           /   \
           +   2
         /   \
        min  max

### Exercise 2-11

Compare the performance of `lookup` and `nrlookup`. How expensive is recursion
compared to iteration?

**Answer**: The benchmark program `tree_lookup_bench` (`tree_lookup_bench.c`) creates a tree mapping `n_items` (command line argument) random strings to random integers. The lookup functions are very fast, so that they need to be executed multiple times to measure any significant time.

Here's the output of the benchmark program that maps 2 million strings of the
length 20 to random integers, and calls the lookup function 5 million times
with the same lookup string:

    $ make tree_lookup_bench && ./tree_lookup_bench 2000000
    recursive: 3.880s for 5000000 calls
    iterative: 2.970s for 5000000 calls

The iterative version works significantly faster. (The comparison is only fair
if both lookups fail or succeed with the same string.)

### Exercise 2-12

Use in-order traversal to create a sort routine. What time complexity does it
have? Under what conditions might it behave poorly? How does its performance
compare to our quicksort and a library version?

**Answer**: See `treesort.c` (`make treesort && ./treesort`). The time
complexity for inserting one item is `O(log n)`, and, thus, `O(n * log n)` for
inserting `n` items. Traversing `n` items in-place for storage in an array is
`O(n)` again, which is smaller than `O(n * log n)`. Tree sort has the time
complexity `O(n * log n)`, but requires more memory than quicksort: The values
are stored twice (array and tree), and each value has two extra pointers.

In `sort_benchmark.c`, the three sort approaches are compared as follows (`make
sort_bench`):

    $ ./sort_bench 5000000
    treesort:       13.000
    quicksort:      9.000
    libsort:        7.000

    $ ./sort_bench 10000000
    treesort:       31.000
    quicksort:      21.000
    libsort:        16.000

Even though `treesort` has a low runtime complexity, it is outperformed by
`quicksort` and the standard library implementation. The overhead of building
up the tree structure seems to have a big impact if `n` is relatively small.

### Exercise 2-13

Devise and implement a set of tests for verifying that the tree routines are
correct.

**Answer**: See `tree_test.c` (`make tree_test && ./tree_test`).
