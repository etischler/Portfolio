all:bTree

bTree: bTree_main.o
	g++ bTree_main.o -o bTree
bTree_main.o: bTree_main.cpp 
	g++ -c bTree_main.cpp #project1a5.cpp
#project1a5.o: project1a5.cpp 
	#g++ -c -Wall project1a5.cpp #sDeque_bTree_main.cpp

clean:
	rm bTree_main.o bTree