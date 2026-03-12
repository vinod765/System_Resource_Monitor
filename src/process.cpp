#include "process.h"

#include<dirent.h>
#include<fstream>
#include<string>
#include<vector>
#include<map>
#include<algorithm>


using namespace std;

static map<int, unsigned long long> pid_history;
static unsigned long long last_total_cpu_time = 0;

double get_memory_usage(int pid){
    string path = "/proc/" + to_string(pid) + "/smaps_rollup";
    ifstream file(path);

    string key;
    double pss_kb = 0;
    string unit;

    while (file>>key){
        if (key == "Pss:"){
            file>>pss_kb>>unit;
            return pss_kb / 1024.0;
        }

        string skip;
        getline(file, skip);
    }

    return 0.0;
}

long get_process_cpu_time(int pid){
    string path = "/proc/" + to_string(pid) + "/stat";
    ifstream file(path);

    if(!file) return 0;

    string ignore;
    unsigned long long utime, stime;

    for(int i=0;i<13;i++)file>>ignore;

    file>>utime>>stime;

    return utime + stime;
}

long get_total_cpu_time()
{
    ifstream file("/proc/stat");

    string cpu;
    unsigned long long user,nice,system,idle,iowait,irq,softirq,steal;

    file>>cpu>>user>>nice>>system>>idle>>iowait>>irq>>softirq>>steal;

    return user + nice + system + idle + iowait + irq + softirq + steal;
}

vector<Process> getProcesses(){
    unsigned long long current_total_cpu_time = get_total_cpu_time();
    unsigned long long total_diff = current_total_cpu_time - last_total_cpu_time;

    last_total_cpu_time = current_total_cpu_time;

    vector<Process> processes;

    DIR* dir = opendir("/proc");
    struct dirent* entry;

    while((entry = readdir(dir)) != NULL) {
        int pid = atoi(entry->d_name);

        if(pid > 0){
            string comm_path= "/proc/" + to_string(pid) + "/comm";
            ifstream file(comm_path);

            string name;

            if(file>>name){
                Process p;

                p.pid = pid;
                p.name = name;

                p.memory = get_memory_usage(pid);

                unsigned long long current_proc_time = get_process_cpu_time(pid);
                unsigned long long prev_proc_time = 0;

                if(pid_history.count(pid))prev_proc_time = pid_history[pid];

                unsigned long long proc_diff = current_proc_time - prev_proc_time;
                pid_history[pid] = current_proc_time;

                if (total_diff > 0) {
                    p.cpu = (double)proc_diff / total_diff * 100.0;
                } else {
                    p.cpu = 0.0;
                }

                processes.push_back(p);
            }
        }
    }

    closedir(dir);

    sort(processes.begin(), processes.end(), [](const Process& a, const Process& b){
        if(a.cpu != b.cpu)return a.cpu > b.cpu;

        if (a.memory != b.memory)return a.memory > b.memory;

        return a.pid < b.pid;
    });

    return processes;
}