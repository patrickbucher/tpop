CFLAGS=-Wall -g
CC=gcc
CPPC=g++

.PHONY: bench test clean

treesort: treesort.o tree.o
	${CC} ${CFLAGS} -o $@ treesort.o tree.o

bench: tree_lookup_bench sort_bench
	./tree_lookup_bench
	./sort_bench 1000000

test: tree_test GenericListTest.class listtemplate_test genericlist_test
	java -ea GenericListTest
	./listtemplate_test
	./genericlist_test
	./tree_test

tree_lookup_bench: tree_lookup_bench.o tree.o
	${CC} ${CFLAGS} -o $@ tree_lookup_bench.o tree.o

sort_bench: sort_bench.o tree.o treesort.c nv_quicksort.c
	${CC} ${CFLAGS} -o $@ sort_bench.o tree.o

tree_test: tree_test.o tree.o
	${CC} ${CFLAGS} -o $@ tree_test.o tree.o

GenericListTest.class: GenericListTest.java GenericList.class
	javac GenericListTest.java

listtemplate_test: listtemplate_test.cpp
	${CPPC} ${CFLAGS} -o $@ listtemplate_test.cpp

genericlist_test: genericlist_test.c
	${CC} ${CFLAGS} -o $@ genericlist_test.c

GenericList.class: GenericList.java
	javac GenericList.java

listtemplate: listtemplate.cpp
	${CPPC} ${CFLAGS} -o $@ listtemplate.cpp

genericlist: genericlist.c
	${CC} ${CFLAGS} -o $@ genericlist.c

listtest: listtest.o list.o
	${CC} ${CFLAGS} -o $@ listtest.o list.o

.SUFFIXES: .c .o

.c.o:
	${CC} ${CFLAGS} -c $<

clean:
	rm -f *.o
	rm -f *.class
	rm -f *.core
	rm -f listtemplate listtest genericlist
	rm -f listtemplate_test genericlist_test
	rm -f tree_test tree_lookup_bench treesort sort_bench
