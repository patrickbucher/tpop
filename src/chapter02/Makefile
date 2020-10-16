CFLAGS=-Wall -g
CC=gcc
CPPC=g++

.PHONY: all test clean

all: GenericList.class listtemplate genericlist listtest

test: GenericListTest.class listtemplate_test genericlist_test
	java -ea GenericListTest
	./listtemplate_test
	./genericlist_test

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

listtest.o: listtest.c
	${CC} ${CFLAGS} -c -o $@ $<

list.o: list.c
	${CC} ${CFLAGS} -c -o $@ $<

clean:
	rm -f *.o
	rm -f *.class
	rm -f listtemplate listtest genericlist
	rm -f listtemplate_test genericlist_test
