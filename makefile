visualizer: main.o
	g++ main.o -o visualizer

main.o: main.cpp
	g++ -c main.cpp