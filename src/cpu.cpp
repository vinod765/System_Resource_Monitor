#include "cpu.h"
#include<iostream>
#include<fstream>
#include<string>
#include<thread>
#include<chrono>

using namespace std;

double cpu_usage() {
    ifstream file("/proc/stat");

    string cpu;
    unsigned long long user, nice, system, idle, iowait, irq, softirq, steal;

    file>>cpu>>user>>nice>>system>>idle>>iowait>>irq>>softirq>>steal;

    unsigned long long total1 = user + nice + system + idle + iowait + irq + softirq + steal;
    unsigned long long idle1 = idle + iowait;

    this_thread::sleep_for(chrono::milliseconds(100));

    file.clear();
    file.seekg(0, ios::beg);

    file>>cpu>>user>>nice>>system>>idle>>iowait>>irq>>softirq>>steal;

    unsigned long long total2 = user + nice + system + idle + iowait + irq + softirq + steal;
    unsigned long long idle2 = idle + iowait;

    unsigned long long totalDiff = total2 - total1;
    unsigned long long idleDiff = idle2 - idle1;

    if(totalDiff == 0)return 0.0;
    
    double usage = (1.0 - (double)idleDiff / totalDiff) * 100;

    return usage;
}