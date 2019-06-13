TARGET=ga
CXX=clang++
CFLAGS= -Wall -Wextra -pedantic -O2 --std=c++2a
DEPS=Chrom.h ga.h fn.h
all : main.o
	$(CXX) $< $(CFLAGS) -o $(TARGET)
%.o: %.cpp $(DEPS)
	$(CXX) $< $(CFLAGS) -c -o $@
.PHONY: clean
clean:
	rm -r *.o
