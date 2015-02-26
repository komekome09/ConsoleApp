all: main.cpp
	g++ main.cpp -lncurses -o test

run:
	./test
