#include <iostream>
#include <string>
#include "./main_memory/main_memory.h"
#include "./cpu_alloc/cpu_alloc.h"
#include<bits/stdc++.h> 
#include <thread>
#include <unistd.h>

using namespace std;

void push(MainMemory *m1,int pid,vector<string> data,string op,int alloc_size,vector<int> proc_list){
    m1->push(pid,data,op,alloc_size,proc_list);
    return;
}

void change(MainMemory *m1,int pid, string op){
    m1->change_op(pid,op);
    return;
}
int main(){
    // Initialize a list of all the process address that we own
    vector<int> proc_list;
    for(int i=0; i<MAX_PROC; i++){
        proc_list.push_back(i);
    }

    // ---- Initialize this proc list ----
    CPUAlloc c1 = CPUAlloc(proc_list);
    // CPUAlloc c2 = CPUAlloc(proc_list);

    cout<<"pid : "<<c1.getpid()<<endl;
    // cout<<"pid : "<<c2.getpid()<<endl;

    // ---- Main memory operations ----
    MainMemory *m1 = m1->getInstance(); // Make size of the main memory as fixed. Internally 10
    // determine operations
    vector<string> data = {"2","3", "0"}; // Always the last entry is for writeback
    string operation = "add";
    int allocation_size = data.size() + 1; // 1 more for the operation
    // I should probably throw exceptions here instead of return value checking like C
    // TODO : Make into exception
    // if(!m1->push(c1.getpid(),data,operation,allocation_size,proc_list)){
    //     cout<<"Push error"<<endl;
    // }


    thread th1(push,m1,c1.getpid(),data,operation,allocation_size,proc_list);
    operation = "sub";
    sleep(1);
    thread th2(change,m1,c1.getpid(),operation);
    // thread th1(foo,m1,3);

    th1.join();
    th2.join();
    // thread(m1->change_op(c1.getpid(),operation));
    // cout<<"OP done -------------------------\n";
    // operation = "sub";
    m1->display_memory();
    // //If you wish to change the operation on the same data. 
    // //i.e same data different CPU and local cache ~ Condition for concurrancy
    //  m1->change_op(c1.getpid(),operation);

    //Display the contents of the RAM.
    // m1->display_memory();
    // ---- Release the process id that we had taken ----
    // c1.deallocate(proc_list);
    // c2.deallocate(proc_list);
    return 0;
}



  //uncomment later
    /*
    if(!m1->push(c2.getpid(),data,operation,allocation_size,proc_list)){
        cout<<"Push error"<<endl;
    }*/
    
    //Pushing again for the same PID should give you an error as data is already in the RAM
    // if(!m1->push(c1.getpid(),data,operation,allocation_size,proc_list)){
    //     cout<<"Push error"<<endl;
    // }
    /*
    if(!m1->push(c2.getpid(),data,operation,allocation_size,proc_list)){
        cout<<"Push error"<<endl;
    }*/