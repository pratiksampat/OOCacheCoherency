#include <iostream>
#include "cpu_alloc.h"
#include <vector>

using namespace std;

CPUAlloc::CPUAlloc(vector<int> &proc_list){
    int index = rand() % proc_list.size(); // pick a random index
    pid = proc_list[index]; // a random value taken from that list
    proc_list.erase(proc_list.begin() + index);
}

void CPUAlloc::deallocate(vector<int> &proc_list){
    proc_list.push_back(pid);
}

int CPUAlloc::getpid(){
    return pid;
}