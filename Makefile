output: main.o
	g++ main.o -o output -l sqlite3


main.o: main.cc Account.h Bank.h SQL.h
	g++ -c main.cc -l sqlite3

clean:
	rm *.o 
