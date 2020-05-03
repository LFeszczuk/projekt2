CXXFLAGS=-g -Iinc -Wall -pedantic -std=c++0x -std=c++1y

__start__: grafowanie
	./grafowanie

grafowanie: main.o matrix.o list.o bellman.o 
	g++ -Wall -pedantic -std=c++0x -std=c++1y -o grafowanie main.o matrix.o list.o bellman.o
	 


main.o:  main.cpp bellman.hpp list.hpp matrix.hpp graph.hpp
	g++ -c ${CXXFLAGS} -o  main.o main.cpp

matrix.o: matrix.cpp matrix.hpp graph.hpp
	g++ -c ${CXXFLAGS} -o matrix.o matrix.cpp

list.o: list.cpp list.hpp graph.hpp
	g++ -c ${CXXFLAGS} -o list.o list.cpp

bellman.o: bellman.cpp bellman.hpp list.hpp matrix.hpp graph.hpp
	g++ -c ${CXXFLAGS} -o bellman.o bellman.cpp


clean:
	rm -f *.o sortowanie