OBJS = main.o binarytree.o node.o
CC = g++
FLAGS = -Wall -std=c++0x
CFLAGS = -Wall -c -std=c++0x

MoreTrees: $(OBJS)
	$(CC) $(FLAGS) $(OBJS) -o MoreTrees

main.o: main.cc binarytree.h node.h data
	$(CC) $(CFLAGS) main.cc

binarytree.o: binarytree.cc binarytree.h node.h data
	$(CC) $(CFLAGS) binarytree.cc

node.o: node.cc node.h data
	$(CC) $(CFLAGS) node.cc

debug: main.cc binarytree.cc node.cc binarytree.h node.h data
	$(CC) -g -std=c++0x main.cc binarytree.cc node.cc -o MoreTrees
	gdb MoreTrees

clean:
	rm *.o MoreTrees
