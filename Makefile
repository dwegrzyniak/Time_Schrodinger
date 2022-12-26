CC = g++
LIBS = -lncurses
GFLAGS = -Wall -pedantic -O2 -std=c++17
all:	wave
wave:	main.o wave.o
	$(CC) -o wave main.o wave.o $(GFLAGS) $(LIBS)
	
wave.o: wave.cpp wave.hpp
	$(CC) -o wave.o -c wave.cpp $(GFLAGS)

kms01.o:	main.cpp wave.hpp
	$(CC) -o main.o -c wave.cpp $(GFLAGS)
