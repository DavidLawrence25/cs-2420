main.exe: main.o palindrome.o
	g++ -std=c++23 -I ../.. -o main.exe main.o palindrome.o

main.o: main.cc
	g++ -std=c++23 -I ../.. -o main.o -c main.cc

palindrome.o: palindrome.cc
	g++ -std=c++23 -I ../.. -o palindrome.o -c palindrome.cc

debug: main.cc palindrome.cc
	g++ -std=c++23 -I ../.. -o main.exe main.cc palindrome.cc -g

tidy: main.exe
	rm -f main.o
	rm -f palindrome.o

clean:
	rm -f main.o
	rm -f palindrome.o
	rm -f main.exe
	rm -f log.txt
	rm -f log.json
