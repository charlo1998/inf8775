CXXFLAGS= -Wall -g  

all: main



municipalite.o : municipalite.cpp 
	g++ -c municipalite.cpp $(CXXFLAGS)

circonscription.o : circonscription.cpp municipalite.cpp
	g++ -c circonscription.cpp $(CXXFLAGS)

heuristique.o: heuristique.cpp municipalite.cpp circonscription.cpp
	g++ -c heuristique.cpp $(CXXFLAGS)

main.o : main.cpp heuristique.cpp
	g++ -c main.cpp $(CXXFLAGS)

main: heuristique.o main.o municipalite.o circonscription.o
	g++ -o main main.o  municipalite.o circonscription.o heuristique.o $(CXXFLAGS)

clean: 
	rm -f *.o 
	rm -f main