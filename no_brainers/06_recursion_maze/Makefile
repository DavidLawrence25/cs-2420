main.exe: main.o maze.o
	g++ -std=c++23 -I ../.. -o main.exe main.o maze.o

main.o: main.cc
	g++ -std=c++23 -I ../.. -o main.o -c main.cc

maze.o: maze.cc
	g++ -std=c++23 -I ../.. -o maze.o -c maze.cc

debug: main.cc maze.cc
	g++ -std=c++23 -I ../.. -o main.exe main.cc maze.cc -g

tidy: main.exe
	rm -f main.o
	rm -f maze.o

clean:
	rm -f main.o
	rm -f maze.o
	rm -f main.exe
	rm -f log.txt
	rm -f log.json
