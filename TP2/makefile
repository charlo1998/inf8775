CXXFLAGS= -Wall -g  

all: main

restaurant.o: restaurant.cpp
	g++ -c restaurant.cpp $(CXXFLAGS)

glouton.o: restaurant.o glouton.cpp
	g++ -c glouton.cpp $(CXXFLAGS)

heuristic.o: restaurant.o glouton.o
	g++ -c heuristic.cpp $(CXXFLAGS)

progdyn.o: progdyn.cpp restaurant.cpp
	g++ -c progdyn.cpp $(CXXFLAGS)

chronometre.o : progdyn.cpp restaurant.cpp heuristic.cpp glouton.cpp
	g++ -c chronometre.cpp $(CXXFLAGS)

main.o : main.cpp progdyn.cpp restaurant.cpp heuristic.cpp chronometre.cpp
	g++ -c main.cpp $(CXXFLAGS)

main: glouton.o progdyn.o main.o restaurant.o heuristic.o chronometre.o
	g++ -Wl,--as-needed -o main main.o chronometre.o heuristic.o progdyn.o glouton.o restaurant.o $(CXXFLAGS)
chrono_main.o: chrono_main.cpp
	g++ -c chrono_main.cpp
chrono_main: chrono_main.o glouton.o progdyn.o restaurant.o heuristic.o chronometre.o
	g++ -Wl,--as-needed -o chrono_main chrono_main.o chronometre.o heuristic.o progdyn.o glouton.o restaurant.o
clean: 
	rm -f *.o 
	rm -f main
	rm -f chrono_main