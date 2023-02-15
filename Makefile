output: main.o
	g++ main.o -o output

main.o: main.cpp Account.h Bank.h
	g++ -c main.cpp

clean:
	rm *.o 