main.exe: main.o person.o
	g++ -std=c++23 -I ../.. -o main.exe main.o person.o

main.o: main.cc
	g++ -std=c++23 -I ../.. -o main.o -c main.cc

person.o: person.cc
	g++ -std=c++23 -I ../.. -o person.o -c person.cc

debug: main.cc person.cc
	g++ -std=c++23 -I ../.. -o main.exe main.cc person.cc -g

tidy: main.exe
	rm -f main.o
	rm -f person.o

clean:
	rm -f main.o
	rm -f person.o
	rm -f main.exe
	rm -f log.txt
	rm -f log.json
