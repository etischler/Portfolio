all:search

search: search.o
	g++ search.o -o search
search.o: search.cpp 
	g++ -c search.cpp #project1a5.cpp
#project1a5.o: project1a5.cpp 
	#g++ -c -Wall project1a5.cpp #sDeque_main.cpp

