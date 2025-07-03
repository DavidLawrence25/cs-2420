main.exe: main.o point.o
	g++ -std=c++23 -I ../.. -o main.exe main.o point.o

main.o: main.cc
	g++ -std=c++23 -I ../.. -o main.o -c main.cc

point.o: point.cc
	g++ -std=c++23 -I ../.. -o point.o -c point.cc

debug: main.cc point.cc
	g++ -std=c++23 -I ../.. -o main.exe main.cc point.cc -g

tidy: main.exe
	rm -f main.o
	rm -f point.o

clean:
	rm -f main.o
	rm -f point.o
	rm -f main.exe
	rm -f log.txt
	rm -f log.json
