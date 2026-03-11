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
    long user, nice, system, idle;

    file>>cpu>>user>>nice>>system>>idle;

    long total1 = user + nice + system + idle;
    long idle1 = idle;

    this_thread::sleep_for(chrono::milliseconds(100));

    file.close();
    file.open("/proc/stat");

    file>>cpu>>user>>nice>>system>>idle;

    long total2 = user + nice + system + idle;
    long idle2 = idle;

    long totalDiff = total2 - total1;
    long idleDiff = idle2 - idle1;

    double usage = (1.0 - (double)idleDiff / totalDiff) * 100;

    return usage;
}