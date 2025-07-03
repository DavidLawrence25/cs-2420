main.exe: main.o subsequence.o
	g++ -std=c++23 -I ../.. -o main.exe main.o subsequence.o

main.o: main.cc
	g++ -std=c++23 -I ../.. -o main.o -c main.cc

subsequence.o: subsequence.cc
	g++ -std=c++23 -I ../.. -o subsequence.o -c subsequence.cc

debug: main.cc subsequence.cc
	g++ -std=c++23 -I ../.. -o main.exe main.cc subsequence.cc -g

tidy: main.exe
	rm -f main.o
	rm -f subsequence.o

clean:
	rm -f main.o
	rm -f subsequence.o
	rm -f main.exe
	rm -f log.txt
	rm -f log.json
