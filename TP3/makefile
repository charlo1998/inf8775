CXXFLAGS= -Wall -g  

all: main


algo.o: algo.cpp
	g++ -c algo.cpp $(CXXFLAGS)

utils.o: utils.cpp
	g++ -c utils.cpp $(CXXFLAGS)

main.o : main.cpp algo.cpp
	g++ -c main.cpp $(CXXFLAGS)

main: algo.o main.o utils.o
	g++ -o main main.o algo.o utils.o $(CXXFLAGS)

clean: 
	rm -f *.o 
	rm -f main
	rm -f chrono_main