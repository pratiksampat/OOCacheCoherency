CC = g++
CFLAGS  = -g -Wall

default: all

all:  cpu_alloc.o main_memory.o directory.o cpu_avail.o cpu.o cache.o main.o 
	$(CC) $(CFLAGS) -o main cpu_alloc.o main_memory.o directory.o cpu_avail.o cpu.o cache.o main.o

cpu_alloc.o: cpu_alloc.cpp cpu_alloc.h
	$(CC) $(CFLAGS) -c cpu_alloc.cpp

main_memory.o:  main_memory.cpp main_memory.h
	$(CC) $(CFLAGS) -c main_memory.cpp

directory.o: directory.cpp directory.h
	$(CC) $(CFLAGS) -c directory.cpp

cpu_avail.o: cpu_avail.cpp cpu_avail.h
	$(CC) $(CFLAGS) -c cpu_avail.cpp

cpu.o: cpu.cpp cpu.h
	$(CC) $(CFLAGS) -c cpu.cpp

cache.o: cache.cpp cache.h
	$(CC) $(CFLAGS) -c cache.cpp

main.o:  main.cpp main_memory.h 
	$(CC) $(CFLAGS) -c main.cpp

clean: 
	$(RM) *.o
	$(RM) main