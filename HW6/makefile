OBJS = main.o bubble.o quick.o heap.o
CC = g++
FLAGS = -Wall -std=c++0x
CFLAGS = -Wall -c -std=c++0x

Sorting: $(OBJS)
	$(CC) $(FLAGS) $(OBJS) -o Sorting

main.o: main.cc bubble.h quick.h heap.h data
	$(CC) $(CFLAGS) main.cc

bubble.o: bubble.cc bubble.h
	$(CC) $(CFLAGS) bubble.cc

quick.o: quick.cc quick.h
	$(CC) $(CFLAGS) quick.cc

heap.o: heap.cc heap.h
	$(CC) $(CFLAGS) heap.cc

debug: main.cc bubble.cc quick.cc heap.cc bubble.h quick.h heap.h data
	$(CC) -g -std=c++0x main.cc bubble.cc quick.cc heap.cc -o Sorting
	gdb Sorting

clean:
	rm *.o Sorting