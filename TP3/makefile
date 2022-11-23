CXXFLAGS= -Wall -g  

all: main


algo.o: algo.cpp
	g++ -c algo.cpp $(CXXFLAGS)

municipalite.o : municipalite.cpp 
	g++ -c municipalite.cpp $(CXXFLAGS)

circonscription.o : circonscription.cpp municipalite.cpp
	g++ -c circonscription.cpp $(CXXFLAGS)

utils.o: utils.cpp municipalite.cpp circonscription.cpp 
	g++ -c utils.cpp $(CXXFLAGS)
main.o : main.cpp algo.cpp
	g++ -c main.cpp $(CXXFLAGS)

main: algo.o main.o utils.o
	g++ -o main main.o  municipalite.o circonscription.o algo.o utils.o $(CXXFLAGS)

clean: 
	rm -f *.o 
	rm -f main