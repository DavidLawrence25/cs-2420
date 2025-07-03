main.exe: main.o date.o
	g++ -std=c++23 -I ../.. -o main.exe main.o date.o

main.o: main.cc
	g++ -std=c++23 -I ../.. -o main.o -c main.cc

date.o: date.cc
	g++ -std=c++23 -I ../.. -o date.o -c date.cc

debug: main.cc date.cc
	g++ -std=c++23 -I ../.. -o main.exe main.cc date.cc -g

tidy: main.exe
	rm -f main.o
	rm -f date.o

clean:
	rm -f main.o
	rm -f date.o
	rm -f main.exe
	rm -f log.txt
	rm -f log.json
