#ifndef CPU_H
#define CPU_H

#include <map>
#include "cache.h"

class Directory;
class CPU
{
    private:
    Directory *dir;
    public:
    CPU();
    void execute(int, std::string, Cache );
    void modify(int pid,int new_val);
};
#endif