CFLAGS=-Wall -g
CC=gcc
CPPC=g++

.PHONY: clean

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
	rm -f listtemplate listtest genericlist
