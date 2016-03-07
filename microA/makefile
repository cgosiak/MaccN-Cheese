CXX = g++
CC = g++
FLAGS = -std=c++11

all:   microA 

microA: microA.cpp maparse.o mascan.o macode.o
	$(CXX) $(FLAGS) maparse.o mascan.o macode.o microA.cpp -o microA

maparse.o: maparse.cpp
	$(CXX) $(FLAGS) -c maparse.cpp

mascan.o: mascan.cpp
	$(CXX) $(FLAGS) -c mascan.cpp

macode.o: macode.cpp
	$(CXX) $(FLAGS) -c macode.cpp

clobber:
	rm -f *.o *.exe *.lis *.obj core microA sam macc trace.txt

