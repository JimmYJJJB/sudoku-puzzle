all:	main

main: main.o
	g++ main.o -o main

main.o: main.cpp puzzle.h
	g++ -c main.cpp puzzle.h -std=c++11

clean:
	rm -f *.o main *.gch
