CFLAGS = -Wall -fpic -coverage -lm

rngs.o: rngs.h rngs.c
	gcc -c rngs.c -g  $(CFLAGS)

dominion.o: dominion.h dominion.c rngs.o
	gcc -c dominion.c -g  $(CFLAGS)
	
randTests: dominion.o randomtestcouncilroom.c
	gcc -o randTest randomtestcouncilroom.c -g dominion.o rngs.o $(CFLAGS)

all: dominion.o randomtestcouncilroom.c randomtestadventurer.c randomtestvillage.c
	echo "Result for running Dominion random card tests:" > randtestcouncilroom.out
	
	echo "randomtestcouncilroom.c" >> randtestcouncilroom.out
	gcc -o randomtestcouncilroom randomtestcouncilroom.c -g dominion.o rngs.o $(CFLAGS)
	./randomtestcouncilroom >> randtestcouncilroom.out
	
	gcov dominion.o -b >> randtestcouncilroom.out
	cat dominion.c.gcov >> randtestcouncilroom.out
	
	echo "Result for running Dominion random card tests:" > randtestadventurer.out
	
	echo "randomtestadventurer.c" >> randtestadventurer.out
	gcc -o randomtestadventurer randomtestadventurer.c -g dominion.o rngs.o $(CFLAGS)
	./randomtestadventurer >> randtestadventurer.out
	
	gcov dominion.o -b >> randtestadventurer.out
	cat dominion.c.gcov >> randtestadventurer.out
	
	echo "Result for running Dominion random card tests:" > randtestvillage.out
	
	echo "randomtestvillage.c" >> randtestvillage.out
	gcc -o randomtestvillage randomtestvillage.c -g dominion.o rngs.o $(CFLAGS)
	./randomtestvillage >> randtestvillage.out
	
	gcov dominion.o -b >> randtestvillage.out
	cat dominion.c.gcov >> randtestvillage.out
	
clean:
	rm -f *.o playdom.exe playdom player player.exe  *.gcov *.gcda *.gcno *.so *.out testDrawCard testDrawCard.exe
