output: main.o bank.o
	g++ main.o bank.o -o output

bank.o: bank.cpp Bank.h Account.h
	g++ -c bank.cpp

main.o: main.cpp
	g++ -c main.cpp

clean:
	rm *.o output