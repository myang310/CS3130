OBJS = main.o linkedlist.o transaction.o
CC = g++
FLAGS = -Wall -std=c++0x
CFLAGS = -Wall -c -std=c++0x

LinkedList: $(OBJS)
	$(CC) $(FLAGS) $(OBJS) -o LinkedList

main.o: main.cc transaction.h node.h linkedlist.h
	$(CC) $(CFLAGS) main.cc

listedlist.o: linkedlist.cc linkedlist.h transaction.h node.h
	$(CC) $(CFLAGS) linkedlist.cc

transaction.o: transaction.cc transaction.h
	$(CC) $(CFLAGS) transaction.cc

debug: main.cc linkedlist.cc transaction.cc linkedlist.h transaction.h node.h data
	$(CC) -g -std=c++0x main.cc linkedlist.cc transaction.cc -o LinkedList
	gdb LinkedList

clean:
	rm *.o LinkedList
