main.exe: main.o bracket_check.o
	g++ -std=c++23 -I ../.. -o main.exe main.o bracket_check.o

main.o: main.cc
	g++ -std=c++23 -I ../.. -o main.o -c main.cc

bracket_check.o: bracket_check.cc
	g++ -std=c++23 -I ../.. -o bracket_check.o -c bracket_check.cc

debug: main.cc bracket_check.cc
	g++ -std=c++23 -I ../.. -o main.exe main.cc bracket_check.cc -g

tidy: main.exe
	rm -f main.o
	rm -f bracket_check.o

clean:
	rm -f main.o
	rm -f bracket_check.o
	rm -f main.exe
	rm -f log.txt
	rm -f log.json
