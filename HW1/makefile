OBJS = main.o
CC = g++
FLAGS = -Wall
CFLAGS = -Wall -c

Review: $(OBJS)
	$(CC) $(FLAGS) $(OBJS) -o Review

main.o: main.cc record.h transaction.h masterfile transactionfile
	$(CC) $(CFLAGS) main.cc

debug: main.cc record.h transaction.h masterfile transactionfile
	$(CC) -g main.cc -o Review
	gdb Review

clean:
	rm *.o Review
