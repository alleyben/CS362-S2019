CFLAGS = -Wall -fpic -coverage -lm -std=c99

default:
	gcc -o testme testme.c $(CFLAGS)

run:
	./testme

gcov:
	gcov testme.c

clean:
	rm testme *.gcda *.gcno *.gcov *.out
