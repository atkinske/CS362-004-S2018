CFLAGS = -Wall -fpic -coverage -lm -std=c99

.PHONY: run
run: testme
	./testme
	
testme: testme.c
	gcc -o testme testme.c $(CFLAGS)

clean:
	rm testme

cleanall: 
	rm testme *.gcda *.gcno *.gcov
