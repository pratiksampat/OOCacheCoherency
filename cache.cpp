#include <iostream>
#include<bits/stdc++.h> 
#include <map>
#include <iterator>
#include "cache.h"
<<<<<<< HEAD
#include "directory.h"
=======
>>>>>>> 16223af75f65e69a6f42c34e3104868e5698a8ff

using namespace std;

#define MAX_SIZE 10

Cache::Cache(){
    this->memory = new c_mem[MAX_SIZE];
    this->index = 0;
    this->size = MAX_SIZE;
}

bool Cache::store(int pid, map<int, string> addrMap){
    // if(index > MAX_SIZE)
    //     return false;
    // this->memory[index].pid = pid;
    // this->memory[index].address = address;
    // this->memory[index].data = data;
    // index++;
    // return true;
    map<int, string>::iterator itr;
    if(index > MAX_SIZE)
        return false;
    for (itr = addrMap.begin(); itr != addrMap.end(); ++itr) { 
        this->memory[index].pid =pid;
        this->memory[index].address = itr->first;
        this->memory[index].data = itr->second;
        index ++;
    }
    return true; 
}

int *Cache::getData(int pid){
    int *data = (int *)malloc(3 * sizeof(int));
    int index = 0;
    for(int i=0; i<this->size; i++){
        if(this->memory[i].address == 0){
            break;
        }
        if(this->memory[i].pid ==  pid){
            data[index++] = stoi(this->memory[i].data);
        }
        // cout<<this->memory[i].address<<"\t";
        // cout<<this->memory[i].pid<<"\t";
        // cout<<this->memory[i].data<<"\t";
        // cout<<endl;
    }
    return data;
}

int Cache::getWritebackAddr(int pid){
    int i = 0;
    for(i=0; i<this->size; i++){
        if(this->memory[i].pid != pid){
            break;
        }
    }
    return this->memory[i-1].address;
}

void Cache::writeBack(int addr, string data){
    for(int i=0; i<this->size; i++){
        if(this->memory[i].address == 0){
            break;
        }
        if(this->memory[i].address == addr){
            this->memory[i].data = data;
        }
    }
}

void Cache::display(){
    cout<< "View of the local cache\n";
    cout<<"Addr"<<"\t"<<"id"<<"\t"<<"data"<<endl;
    for(int i=0; i<this->size; i++){
        if(this->memory[i].address == 0){
            break;
        }
        cout<<this->memory[i].address<<"\t";
        cout<<this->memory[i].pid<<"\t";
        cout<<this->memory[i].data<<"\t";
        cout<<endl;
    }
}
void Cache::modify(int pid,int addr,int new_val)
{
    
    for(int i=0;i<size;i++)
    {
        if(this->memory[i].pid==pid && this->memory[i].address==addr)
        {
            writeBack(addr, to_string(new_val));
            cout << "Modify cache : pid is" << pid<<endl;
            display();
            dir=dir->getInstance();
            dir->finished_update(pid);
            break;
        }
    }
}