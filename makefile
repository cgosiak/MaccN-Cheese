CXX = g++
CC = g++
FLAGS = -std=c++11

all:   microMNC

microMNC: microMNC.cpp mncparse.o mncscan.o mnccode.o
	$(CXX) $(FLAGS) mncparse.o mncscan.o mnccode.o microMNC.cpp -o microMNC

mncparse.o: mncparse.cpp
	$(CXX) $(FLAGS) -c mncparse.cpp

mncscan.o: mncscan.cpp
	$(CXX) $(FLAGS) -c mncscan.cpp

mnccode.o: mnccode.cpp
	$(CXX) $(FLAGS) -c mnccode.cpp

clobber:
	rm -f *.o *.exe *.lis *.obj core micro sam maccc trace.txt

