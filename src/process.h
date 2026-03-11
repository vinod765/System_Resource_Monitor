#ifndef PROCESS_H
#define PROCESS_H

#include <vector>
#include <string>
using namespace std;

struct Process
{
    int pid;
    string name;
};

vector<Process> getProcesses();

#endif