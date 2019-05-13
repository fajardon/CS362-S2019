CFLAGS= -Wall -fpic -coverage -lm -std=c99

testme:
	gcc -o testme -g testme.c $(CFLAGS)
	./testme
	gcov testme.c

clean:
	rm -f testme *.gcov *.gcda *.gcno *.o
