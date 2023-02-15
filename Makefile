output: main.o utils.o
	g++ main.o utils.o -o output

utils.o: utils.cpp Utils.h
	g++ -c utils.cpp

main.o: main.cpp Account.h Bank.h
	g++ -c main.cpp utils.cpp

clean:
	rm *.o 