#include "memory.h"
#include<fstream>
#include<string>
using namespace std;

double memory_usage() {
    ifstream file("/proc/meminfo");

    string key;
    unsigned long long val;
    string unit;

    unsigned long long total = 0;
    unsigned long long available = 0;

    while(file>>key>>val>>unit){
        if(key == "MemTotal:")total = val;

        if(key == "MemAvailable:")available = val;

        if(total > 0 && available > 0)break;
    }

    if(total == 0)return 0.0;

    double used = (double)(total - available) / total * 100.0;

    return used;
}
