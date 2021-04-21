CC=gcc
CFLAGS=-I.

all : parallel_min_max utils.o find_min_max.o process_memory.o parallel_sum

utils.o : utils.h
	$(CC) -o utils.o -c utils.c $(CFLAGS)./tas

find_min_max.o : utils.h find_min_max.h
	$(CC) -o find_min_max.o -c find_min_max.c $(CFLAGS)

parallel_min_max : utils.o find_min_max.o utils.h find_min_max.h
	$(CC) -o parallel_min_max utils.o find_min_max.o parallel_min_max.c $(CFLAGS)

process_memory.o: 
	$(CC) -c process_memory.c 
	$(CC) process_memory.o -o process_memory $(CFLAGS)

parallel_sum :
	$(CC) -pthread parallel_sum.c utils.c -o parallel_sum $(CFLAGS)

clean :
	rm utils.o find_min_max.o parallel_min_max process_memory process_memory.o parallel_sum