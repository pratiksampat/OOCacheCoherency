#ifndef MAINMEMORY_H
#define MAINMEMORY_H

#include <string>
#include <vector>
#include <map>
#include "../directory/directory.h"

struct mem{
    int pid;
    int address;
    std::string type;
    std::string data;
    bool valid=false;
};
class MainMemory{
private:
    int size;
    int last_addr;
    int size_left;
    mem *memory;
    Directory *dir;
    MainMemory(int);
    // int *arr;
    static bool singleFlag;
    static MainMemory *s_obj;
    int find(int);
public:
    static MainMemory *getInstance();
    bool push(int,std::vector<std::string>,std::string,int,std::vector<int>);
    void change_op(int, std::string);
    void display_memory();
    std::map<int, std::string> getData(int);
    std::string getOp(int);
    void writeBack(int, std::string, std::string);
    void removemem(int pid);
};

#endif