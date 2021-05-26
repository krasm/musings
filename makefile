CXX=c++
CXXFLAGS=-g -Wall -I. -I$(HOME)/opt/catch2/include -L$(HOME)/opt/catch2/lib

all: test main

test: test.cpp number.hpp
	$(CXX) $(CXXFLAGS) -o $@ $^

main: main.cpp number.hpp
	$(CXX) $(CXXFLAGS) -o $@ $^

clean: 
	- rm test
	- rm main
	- rm *.o
