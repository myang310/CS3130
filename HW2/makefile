OBJS = main.o record.o
CC = g++
FLAGS = -Wall -std=c++0x
CFLAGS = -Wall -c -std=c++0x
DEBUG = -g -std=c++0x

More_Review: $(OBJS)
	$(CC) $(FLAGS) $(OBJS) -o More_Review

main.o: main.cc record.h inputFile
	$(CC) $(CFLAGS) main.cc

record.o: record.cc record.h inputFile
	$(CC) $(CFLAGS) record.cc

debug: main.cc record.h inputFile
	$(CC) $(DEBUG) main.cc record.cc -o More_Review
	gdb More_Review

clean:
	rm *.o More_Review
