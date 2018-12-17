#ifndef CACHE_H
#define CACHE_H

#include <string>
#include <vector>
#include <map>

class Directory;
struct c_mem{
    int pid;
    int address;
    // char type;
    std::string data;
};
class Cache{
private:
    Directory *dir;
    c_mem *memory;
    int index;
    int size;
public:
    Cache();
    int *getData(int);
    std::map<int, std::string> getAllData(int pid);
    //Type not needed as don't push op to cache
    bool store(int, std::map<int, std::string>);
    void display();
    int getWritebackAddr(int);
    void writeBack(int, std::string);
    void modify(int pid,int addr,int new_val);
};
#endif