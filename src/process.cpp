#include "process.h"
#include <dirent.h>
#include <fstream>
using namespace std;

vector<Process> getProcesses() {
    vector<Process> processes;

    DIR* dir = opendir("/proc");
    struct dirent* entry;

    while ((entry = readdir(dir)) != NULL)
    {
        int pid = atoi(entry->d_name);

        if (pid > 0)
        {
            string path = "/proc/" + to_string(pid) + "/comm";

            ifstream file(path);

            string name;

            if (file >> name)
            {
                Process p;
                p.pid = pid;
                p.name = name;

                processes.push_back(p);
            }
        }
    }

    closedir(dir);

    return processes;
}