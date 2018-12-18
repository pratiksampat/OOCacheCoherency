#include <iostream>
#include<bits/stdc++.h> 
#include <map>
#include <iterator>
#include <algorithm>
#include "cache.h"
#include "../directory/directory.h"

using namespace std;

#define MAX_SIZE 10


Cache::Cache(){
    this->memory = new c_mem[MAX_SIZE];
    this->index = 0;
    this->size = MAX_SIZE;
}

bool Cache::store(int pid, map<int, string> addrMap){
    map<int, string>::iterator itr;
    string token;
    vector<string> v1;
    string data;
    string type;
    if(index > MAX_SIZE)
        return false;
    for (itr = addrMap.begin(); itr != addrMap.end(); ++itr) { 
        this->memory[index].pid =pid;
        this->memory[index].address = itr->first;
        size_t last = 0; 
        size_t next = 0; 
        while ((next = itr->second.find(";", last)) != string::npos) { 
            data =  itr->second.substr(last, next-last);
            last = next + 1; 
        } 
        type  = itr->second.substr(last);

        this->memory[index].data = data;
        this->memory[index].type = type;
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
    }
    return data;
}
map<int, string> Cache::getAllData(int pid){
    map<int, string> returnMap; 
    for(int i=0; i<this->size; i++){
        if(this->memory[i].address == 0){
            break;
        }
        if(this->memory[i].pid == pid){

            returnMap[this->memory[i].address] = this->memory[i].data + ";" + this->memory[i].type;
        }
    }
    return returnMap;
}


int Cache::getWritebackAddr(int pid){
    int i = 0;
    for(i=0; i<this->size; i++){
        if(this->memory[i].pid == pid && this->memory[i].type == "wb"){
            return this->memory[i].address;;
        }
    }
   return -1;
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