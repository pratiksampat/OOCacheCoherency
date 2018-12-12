#ifndef CPUAVAIL_H
#define CPUAVAIL_H
struct cpu_aux
{
    bool is_free;
};
class CPUAvail
{
    private:
        int no_cpu;
        cpu_aux *cpu_meta;
        static bool singleFlag;
        static CPUAvail *s_obj;
        CPUAvail(int);
    public:
        static CPUAvail *getInstance(int);
        void set_avail(int cpu);
        // void set_sizeleft(int cpu,int nsize);
        int choose_cpu();

};
#endif