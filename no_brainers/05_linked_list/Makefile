main.exe: main.o
	g++ -std=c++23 -I ../.. -o main.exe main.o

main.o: main.cc
	g++ -std=c++23 -I ../.. -o main.o -c main.cc

debug: main.cc
	g++ -std=c++23 -I ../.. -o main.exe main.cc -g

tidy: main.exe
	rm -f main.o

clean:
	rm -f main.o
	rm -f main.exe
	rm -f log.txt
	rm -f log.json
