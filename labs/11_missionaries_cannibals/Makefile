main.exe: main.o state.o missionaries_cannibals.o
	g++ -std=c++23 -I ../.. -o main.exe main.o state.o missionaries_cannibals.o

main.o: main.cc
	g++ -std=c++23 -I ../.. -o main.o -c main.cc

state.o: state.cc
	g++ -std=c++23 -I ../.. -o state.o -c state.cc

missionaries_cannibals.o: missionaries_cannibals.cc
	g++ -std=c++23 -I ../.. -o missionaries_cannibals.o -c missionaries_cannibals.cc

debug: main.cc state.cc missionaries_cannibals.cc
	g++ -std=c++23 -I ../.. -o main.exe main.cc state.cc missionaries_cannibals.cc -g

tidy: main.exe
	rm -f main.o
	rm -f state.o
	rm -f missionaries_cannibals.o

clean:
	rm -f main.o
	rm -f state.o
	rm -f missionaries_cannibals.o
	rm -f main.exe
	rm -f log.txt
	rm -f log.json
