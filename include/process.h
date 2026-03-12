#ifndef PROCESS_H
#define PROCESS_H

#include <string>
#include <vector>
using namespace std;

struct Process
{
    int pid;
    string name;
    double cpu;
    double memory;

    unsigned long long last_cpu_time;
};

vector<Process> getProcesses();

#endif