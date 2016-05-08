all:Floyd-Warshall

Floyd-Warshall: exercise4.o
	g++ exercise4.o -o Floyd-Warshall
Floyd-Warshall.o: exercise4.cpp 
	g++ -c exercise4.cpp #project1a5.cpp
#project1a5.o: project1a5.cpp 
	#g++ -c -Wall project1a5.cpp #sDeque_main.cpp

