CC=g++
CFLAGS= -std=c++11 -ggdb

all: Problem4 Problem5

Problem4: P4.cpp
	$(CC) P4.cpp -o Problem4 $(CFLAGS)
	
Problem5: P5.cpp
	$(CC) P5.cpp -o Problem5 $(CFLAGS)

clean:
	rm -f *.o *~ shape1 shape2

