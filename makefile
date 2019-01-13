magos: main.o
	g++ -Wall -std=c++11 main.o -o magos
	-rm *.o
main.o:
	g++ -Wall -std=c++11 -c src/main.cpp -o main.o 