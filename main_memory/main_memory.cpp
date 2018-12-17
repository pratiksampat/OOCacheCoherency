#include <iostream>
#include <vector>
#include <string>
#include "main_memory.h"
#include<bits/stdc++.h> 
#include<map>

using namespace std;

#define MAX_SIZE 10
mutex mainMem;

bool MainMemory::singleFlag = false;
MainMemory* MainMemory::s_obj = NULL;
// Singleton instance
MainMemory* MainMemory::getInstance(){
    mainMem.lock();
    if(!singleFlag){
        // cout<<"New object created\n";
        // int size = MAX_SIZE;
        s_obj = new MainMemory(MAX_SIZE);
        singleFlag = true;
    }
    mainMem.unlock();
    return s_obj;
}

MainMemory :: MainMemory(int size){
    this->size = size;
    this->size_left = size;
    this->memory = new mem[size];
    this->last_addr = 0;
    this->dir=dir->getInstance();
}
bool MainMemory::push(int pid,vector<string> data,string op,int alloc_size,vector<int> proc_list){
    vector<int>::iterator it;
    mainMem.lock();
    if(size_left < alloc_size || find(pid) != -1){
        return false;
    }
    int i = 0;
    // last_addr+=1;
    // base to pass to directory
    int base_addr=last_addr+1000;
    for(i=0; i<alloc_size - 2; i++){
       this->memory[last_addr].address = last_addr+1000;
       this->memory[last_addr].pid = pid;
       this->memory[last_addr].data = data[i];
       this->memory[last_addr].type = "d";
       this->memory[last_addr].valid = true;
       last_addr ++;
    }
    this->memory[last_addr].address = last_addr+1000;
    this->memory[last_addr].pid = pid;
    this->memory[last_addr].data = data[i];
    this->memory[last_addr].type = "wb"; // Data rewrite
    this->memory[last_addr].valid = true; 
    last_addr ++;

    this->memory[last_addr].address = last_addr+1000;
    this->memory[last_addr].pid = pid;
    this->memory[last_addr].data = op;
    this->memory[last_addr].type = "i";
    this->memory[last_addr].valid = true;
    last_addr ++;

    // Kept a print for DEBUG -- Will remove completely when satisfied.
    // cout<<"Addr"<<"\t"<<"id"<<"\t"<<"data"<<"\t"<<"type"<<endl;
    // for(int i=0; i<this->size; i++){
    //     if(this->memory[i].address == 0){
    //         break;
    //     }
    //     cout<<this->memory[i].address<<"\t";
    //     cout<<this->memory[i].pid<<"\t";
    //     cout<<this->memory[i].data<<"\t";
    //     cout<<this->memory[i].type<<"\t";
    //     cout<<endl;
    // }
    this->size_left -= alloc_size;
    cout<<"Size left = "<<size_left<<endl;
    mainMem.unlock();
    dir->choose_cpu(base_addr,alloc_size,pid);
    // ---------- TODO ----------
    // invoke the directory from here 
    return true;
}
void MainMemory::change_op(int pid, string op){
    int index = find(pid);
    //find start address and size
    if(index!=-1)
    { 
        int base_addr=index;
        int size=1;
        while(this->memory[index].type != "i"){
            index++;
            size++;
        }
        mainMem.lock();
        this->memory[index].data = op;
        mainMem.unlock();
        dir->choose_cpu(base_addr,size,pid);
    }

}

void MainMemory::display_memory(){
    cout<<"Addr"<<"\t"<<"id"<<"\t"<<"data"<<"\t"<<"type"<<endl;
    for(int i=0; i<this->size; i++){
        if(this->memory[i].address == 0){
            break;
        }
        cout<<this->memory[i].address<<"\t";
        cout<<this->memory[i].pid<<"\t";
        cout<<this->memory[i].data<<"\t";
        cout<<this->memory[i].type<<"\t";
        cout<<endl;
    }
}

void MainMemory::writeBack(int addr, string data, string op){
    for(int i=0; i<this->size; i++){
        if(this->memory[i].address == 0){
            break;
        }
        if(this->memory[i].address == addr){
            // this->memory[i].type += "_";
            this->memory[i].type = "wb_" + op;
            this->memory[i].data = data;
        }
    }
}
map<int, string> MainMemory::getData(int pid){
    map<int, string> returnMap; 
    for(int i=0; i<this->size; i++){
        if(this->memory[i].address == 0){
            break;
        }
        if(this->memory[i].pid == pid && (this->memory[i].type != "i" )){
            returnMap[this->memory[i].address] = this->memory[i].data;
        }
    }
    return returnMap;
}

string MainMemory::getOp(int pid){
     for(int i=0; i<this->size; i++){
        if(this->memory[i].address == 0){
            break;
        }
        if(this->memory[i].pid == pid && this->memory[i].type == "i"){
            return this->memory[i].data;
        }
    }
    return "Fail";
}

int MainMemory::find(int pid){
    for(int i=0; i<this->size; i++){
        if(this->memory[i].pid == pid && this->memory[i].valid==true){
            return i;
        }
    }
    return -1;
}

//delete from mainmen
void MainMemory::removemem(int pid)
{
    for(int i=0; i<this->size; i++){
        if(this->memory[i].pid == pid){
             this->memory[i].valid=false;
        }
    }
}