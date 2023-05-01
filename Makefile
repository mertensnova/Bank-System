output: main.o
	g++ main.o -o output -l sqlite3


main.o: main.cxx  sql.h accounts.h bank.h
	g++ -c main.cxx -l sqlite3

clean:
	rm *.o 
