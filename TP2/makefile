all: main

restaurant.o: 
	g++ -c restaurant.cpp -Wall -g
glouton.o: restaurant.o
	g++ -c glouton.cpp -Wall -g
dynamique.o:
	g++ -c dynamique.cpp -Wall -g
main.o :
	g++ -c main.cpp -Wall -g
main: glouton.o dynamique.o main.o restaurant.o
	g++ -o main main.o dynamique.o glouton.o restaurant.o
clean: 
	rm *.o 
	rm main