#include <iostream>
#include <vector>
#include <string>
#include "cpu_avail.h"
#include<bits/stdc++.h> 

using namespace std;
bool CPUAvail::singleFlag = false;
CPUAvail* CPUAvail::s_obj = NULL;
mutex m;
CPUAvail * CPUAvail::getInstance(int no_cpu)
{
    m.lock();
    if(!singleFlag){
        // cout<<"New object created\n";
        s_obj = new CPUAvail(no_cpu);
        singleFlag = true;
    }
    m.unlock();
    return s_obj;
}
CPUAvail::CPUAvail(int no_cpu)
{
    this->no_cpu=no_cpu;
    this->cpu_meta=new cpu_aux[no_cpu];
    for(int i=0;i<no_cpu;i++)
    {
        this->cpu_meta[i].is_free=true;
        // this->cpu_meta[i].size_left=3;
        //cout << "free" << this->cpu_meta[i].is_free<<endl;
    }
}
//after cpu finishes oper set to free
void CPUAvail::set_avail(int cpu)
{
    this->cpu_meta[cpu].is_free= !this->cpu_meta[cpu].is_free;
}
int CPUAvail::choose_cpu()
{
    cpu_aux cpu;
    //cout <<"size"<<no_cpu <<endl;
    for(int i=0;i<no_cpu;i++)
    {
        cpu=this->cpu_meta[i];
        if(cpu.is_free)
        {
            this->cpu_meta[i].is_free=false;
            // this->cpu_meta[i].size_left-=size;
            //cout <<"cpu"<<i <<endl;
            return i;
        }
    }
    return -1;
}

