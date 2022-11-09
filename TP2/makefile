CXXFLAGS= -Wall -Wextra

all: main

restaurant.o: restaurant.cpp
	g++ -c restaurant.cpp $(CXXFLAGS)

glouton.o: restaurant.o glouton.cpp
	g++ -c glouton.cpp $(CXXFLAGS)

heuristic.o: restaurant.o glouton.o
	g++ -c heuristic.cpp $(CXXFLAGS)

progdyn.o: progdyn.cpp restaurant.cpp
	g++ -c progdyn.cpp $(CXXFLAGS)

main.o : main.cpp progdyn.cpp restaurant.cpp
	g++ -c main.cpp $(CXXFLAGS)

main: glouton.o progdyn.o main.o restaurant.o heuristic.o
	g++ -o main heuristic.o main.o progdyn.o glouton.o restaurant.o $(CXXFLAGS)

clean: 
	rm *.o 
	rm main