CC=g++
LDFLAGS=-std=c++11 -O3 -lm
SOURCES=graph.cpp main.cpp fibonacci_heap.cpp binary_heap.cpp
OBJECTS=$(SOURCES:.c=.o)
EXECUTABLE=mst
INCLUDES=graph.h fibonacci_heap.h binary_heap.h

all: $(SOURCES) $(EXECUTABLE) 

$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

%.o:  %.c  ${INCLUDES} 
	$(CC) $(CFLAGS)  $< -o $@

clean:
	rm -rf *.o $(EXECUTABLE)
