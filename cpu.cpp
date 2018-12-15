#include <iostream>
#include "cpu.h"
#include<bits/stdc++.h> 
#include "directory.h"
#include "cache.h"
#include "main_memory.h"
using namespace std;

CPU::CPU()
{
    
}
void CPU::execute(int pid, string op, Cache c)
{
    cout <<endl<< "Executing ----------------"<<endl;
    dir=dir->getInstance();
    // cout << "CPU selected: pid is" << pid<<endl;
    c.display();
    int *data = c.getData(pid);

    // Don't use if statements inherit these operations please
    if(op == "add"){
        data[2] = data[0] + data[1];
    }
    else if(op=="sub"){
        data[2]=data[0]-data[1];
    }
    int wb_addr = c.getWritebackAddr(pid);
    cout<< "Wb_Addr : "<< wb_addr<<endl;
    MainMemory *m1 = m1->getInstance();

    //Write to both the main memory and the cache.
    m1->writeBack(wb_addr, to_string(data[2]), op);
    c.writeBack(wb_addr, to_string(data[2]));
    c.display();
    //DEBUG
    // cout << "Sum : "<<data[2]<<endl;
    // for(int i=0; i<2; i++){
    //     cout<<data[i]<<endl;
    // }

    dir->update_map(pid,wb_addr,data[2]);

}
