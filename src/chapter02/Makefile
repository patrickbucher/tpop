.PHONY: clean

listtest: listtest.o list.o
	${CC} ${CFLAGS} -o $@ listtest.o list.o

listtest.o: listtest.c
	${CC} ${CFLAGS} -c -o $@ $<

list.o: list.c
	${CC} ${CFLAGS} -c -o $@ $<

clean:
	rm -f *.o
	rm -f listtest