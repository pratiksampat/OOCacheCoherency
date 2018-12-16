CC = g++
CFLAGS  = -g -Wall -std=c++11 -pthread

default: all

all:  cpu_alloc.o main_memory.o directory.o cpu_avail.o cpu.o cache.o main.o 
	$(CC) $(CFLAGS) -o main cpu_alloc.o main_memory.o directory.o cpu_avail.o cpu.o cache.o main.o

cpu_alloc.o: cpu_alloc/cpu_alloc.cpp cpu_alloc/cpu_alloc.h
	$(CC) $(CFLAGS) -c cpu_alloc/cpu_alloc.cpp

main_memory.o:  main_memory/main_memory.cpp main_memory/main_memory.h
	$(CC) $(CFLAGS) -c main_memory/main_memory.cpp

directory.o: directory/directory.cpp directory/directory.h
	$(CC) $(CFLAGS) -c directory/directory.cpp

cpu_avail.o: cpu_avail/cpu_avail.cpp cpu_avail/cpu_avail.h
	$(CC) $(CFLAGS) -c cpu_avail/cpu_avail.cpp 

cpu.o: cpu/cpu.cpp cpu/cpu.h
	$(CC) $(CFLAGS) -c cpu/cpu.cpp

cache.o: cache/cache.cpp cache/cache.h
	$(CC) $(CFLAGS) -c cache/cache.cpp

main.o:  main.cpp main_memory/main_memory.h 
	$(CC) $(CFLAGS) -c main.cpp

clean: 
	$(RM) *.o
	$(RM) main