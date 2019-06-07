TARGET=ga
CXX=clang++
CFLAGS= -Wall -Wextra -pedantic -O2 --std=c++2a
DEPS=Chrom.h Population.h
all : main.o
	$(CXX) $< $(CFLAGS) -o $(TARGET)
%.o: %.cpp $(DEPS)
	$(CXX) $< $(CFLAGS) -c -o $@
