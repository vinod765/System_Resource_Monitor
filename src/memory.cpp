#include "memory.h"
#include<fstream>
#include<string>
using namespace std;

double memory_usage() {
    ifstream file("/proc/meminfo");

    string key;
    long val;
    string unit;

    long total;
    long available;

    while(file>>key>>val>>unit){
        if(key == "MemTotal:")total = val;

        if(key == "MemAvailable:")available = val;
    }

    double used = total - available;

    return (used / total) * 100.0;
}
