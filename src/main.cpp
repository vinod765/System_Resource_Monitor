#include <thread>
#include <chrono>
#include <vector>

#include "cpu.h"
#include "memory.h"
#include "process.h"
#include "ui.h"

#include <ncurses.h>
using namespace std;

int main()
{
    init_ui();

    while (true){
        double cpu = cpu_usage();
        double mem = memory_usage();

        vector<Process> processes = getProcesses();

        draw_ui(cpu, mem, processes);

        int ch = getch();

        if (ch == 'q')
            break;

    }

    close_ui();

    return 0;
}