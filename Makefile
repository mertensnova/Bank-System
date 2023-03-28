output: main.o
	g++ main.o -o output

main.o: main.cxx Account.h Bank.h
	g++ -c main.cxx

clean:
	rm *.o 