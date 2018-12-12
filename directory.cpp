#include <iostream>
#include <vector>
#include <string>
#include "directory.h"
#include<bits/stdc++.h> 
#include "cpu.h"
#include "cache.h"
#include "main_memory.h"
#include <map>
#include <iterator> 

using namespace std;

bool Directory::singleFlag=false;
Directory* Directory::dir=NULL;

Directory* Directory::getInstance()
{
    if(!singleFlag){
        // cout<<"New object created\n";
        dir = new Directory();
        singleFlag = true;
    }
    return dir;
}
Directory::Directory()
{
    cpu_avail=cpu_avail->getInstance(NO_CPU);
    cpu=new CPU[NO_CPU];
    cache = new Cache[NO_CPU];
    //cout << "yayy"<<endl;
}
void Directory::choose_cpu(int base_addr,int size,int pid)
{
    //cout <<"in dir:: choose cpu " << size <<endl;
    //if pid not in cache
    if(cache_map.find(pid)==cache_map.end())
    {
        cout << "not found in cache :pid is" <<endl;
        cache_counters x;
        x.n_cache=1;
        x.d_cache=0;
        cache_map[pid]=x;
        cout << "n_cache("<<pid<<") : "<< cache_map.at(pid).n_cache <<" d_cache : "<< cache_map.at(pid).d_cache <<endl;
    }
    else
    {
        cout << "found in cache :pid is" <<endl;
        cache_map.at(pid).n_cache+=1;
        cout << cache_map.at(pid).n_cache <<endl;
    }
    //choose cpu and call cpu
    int chosen_cpu=cpu_avail->choose_cpu();
    if(chosen_cpu == -1){
        cout << "NO CPU AVAILABLE : Ideally use wait queue - implementation pending "<<endl;
        exit(0);
    }
    cout << "Chosen CPU : "<<chosen_cpu <<endl;
    // Store in cache
    map<int, string> addrMap;
    MainMemory *m1 = m1->getInstance();
    addrMap = m1->getData(pid);
    string op = m1->getOp(pid);
    cout<< "Operation : "<<op<<endl;
    cache[chosen_cpu].store(pid,addrMap);
    // cache[chosen_cpu].display();

    // cout << "type : "<<typeid(cache[chosen_cpu]).name()<<endl;
    cpu[chosen_cpu].execute(pid,op,cache[chosen_cpu]);

    //DEBUG : Print of address map
    // map<int, string>::iterator itr;
    // cout << "ADDRESS MAP\n";
    // for (itr = addrMap.begin(); itr != addrMap.end(); ++itr) { 
    //     cout << '\t' << itr->first 
    //          << '\t' << itr->second << '\n'; 
    // } 
    
    //cpu[chosen_cpu].execute(base_addr,size,pid);
}
//called by cpu when new value written into cache
void Directory::update_map(int pid,int addr, int new_val)
{
    if(cache_map.find(pid)!=cache_map.end())
    {
        
        //d_cache will be one less than n_cache
        cache_map.at(pid).d_cache=cache_map.at(pid).n_cache-1;
        //update cache ref
        // cout << "update map : d_cache is" <<endl;
        // cout << cache_map.at(pid).d_cache << endl;

        if(cache_map.at(pid).d_cache == 0){
            cout <<endl<< "Consistent -- Exiting" << endl;
            return;    // Don't notify if nobody else is depending on it.
        }
        cache_map.at(pid).address = addr;
        cache_map.at(pid).dirty_val=new_val;
        //notify all cpus
        for(int i=0;i<NO_CPU;i++)
        {
            cpu[i].modify(pid,new_val);
        }
    }
}
//called by cpu when it has updated cache(dirty)
void Directory::finished_update(int pid)
{
    if(cache_map.find(pid)!=cache_map.end())
    {
        cache_map.at(pid).d_cache-=1;
    }
    else
    {
        cout << "not found" <<endl;
    }
}