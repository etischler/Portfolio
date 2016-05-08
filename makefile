all:tDeque

tDeque: tDeque_main.o
	g++ tDeque_main.o -o tDeque
tDeque_main.o: tDeque_main.cpp 
	g++ -c tDeque_main.cpp #project1a5.cpp
#project1a5.o: project1a5.cpp 
	#g++ -c -Wall project1a5.cpp #sDeque_main.cpp

