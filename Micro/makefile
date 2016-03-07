CXX = g++
CC = g++
FLAGS = -std=c++11

all:   microA 

micro: microA.cpp maparse.o mascan.o macode.o
	$(CXX) $(FLAGS) maparse.o mascan.o macode.o microA.cpp -o microA

mparse.o: maparse.cpp
	$(CXX) $(FLAGS) -c maparse.cpp

mscan.o: mascan.cpp
	$(CXX) $(FLAGS) -c mascan.cpp

mcode.o: macode.cpp
	$(CXX) $(FLAGS) -c macode.cpp

clobber:
	rm -f *.o *.exe *.lis *.obj core microA sam macc trace.txt

