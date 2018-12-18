#include <iostream>
#include "cpu.h"
#include<bits/stdc++.h> 
#include "../directory/directory.h"
#include "../cache/cache.h"
#include "../main_memory/main_memory.h"
#include <unistd.h>
using namespace std;

CPU::CPU()
{
    
}
void CPU::execute(int pid, string op, Cache c)
{
    cout <<endl<< "Execution Begun ----------------"<<endl;
    dir=dir->getInstance();
    // cout << "CPU selected: pid is" << pid<<endl;
    c.display();
    int *data = c.getData(pid);
    int result;
    // Don't use if statements inherit these operations please
    if(op == "add"){
        cout<<"Operation ----------------Add"<<endl;
        result = data[0] + data[1];
    }
    else if(op=="mul"){
        cout<<"Operation ----------------Mul"<<endl;
        // cout<<"Data[2] :"<<data[2]<<" Data[1]"<<data[1]<<endl;
        result=data[0] * data[1];
    }
    int wb_addr = c.getWritebackAddr(pid);
    cout<< "Writeback address : "<< wb_addr<<endl;
    MainMemory *m1 = m1->getInstance();

    //Write to both the main memory and the cache.
    
    c.writeBack(wb_addr, to_string(result));
    dir->update_map(pid,wb_addr,result);
    c.display();
    cout<<"Sleeping----------------"<<endl;
    sleep(5);
    //add sleep here
    
    m1->writeBack(wb_addr, to_string(result), op);
    //cpu finished exec
    dir->finished_exec(pid);
    
    //DEBUG
    // cout << "Sum : "<<data[2]<<endl;
    // for(int i=0; i<2; i++){
    //     cout<<data[i]<<endl;
    // }

    

}
