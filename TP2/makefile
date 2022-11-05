all: main

restaurant.o: 
	g++ -c restaurant.cpp -Wall -g
glouton.o: restaurant.o
	g++ -c glouton.cpp -Wall -g
progdyn.o:
	g++ -c progdyn.cpp -Wall -g
main.o :
	g++ -c main.cpp -Wall -g
main: glouton.o progdyn.o main.o restaurant.o
	g++ -o main main.o progdyn.o glouton.o restaurant.o
clean: 
	rm *.o 
	rm main