#ifndef CPUALLOC_H
#define CPUALLOC_H
#include <vector>
#include <iostream>

#define MAX_PROC 8

class CPUAlloc{
    // std::vector<int> *proc_list = new std::vector<int>(MAX_PROC);
    int pid;
public:
    CPUAlloc(std::vector<int> &);
    void deallocate(std::vector<int> &);
    int getpid();
};

#endif