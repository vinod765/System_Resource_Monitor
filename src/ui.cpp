#include <ncurses.h>
#include <vector>
#include <string>

#include "process.h"

/* Draw usage bar (for CPU and Memory) */
void draw_bar(int row, int col, double percent, int width)
{
    int filled = (percent / 100.0) * width;

    mvprintw(row, col, "[");

    for (int i = 0; i < width; i++)
    {
        if (i < filled)
            addch('#');
        else
            addch(' ');
    }

    printw("] %.2f%%", percent);
}


/* Draw process table */
void draw_process_table(int start_row, const std::vector<Process>& processes)
{
    attron(A_BOLD);
    mvprintw(start_row, 2, "PID");
    mvprintw(start_row, 12, "PROCESS");
    attroff(A_BOLD);

    int max_rows = 15;

    for (int i = 0; i < max_rows && i < processes.size(); i++)
    {
        mvprintw(start_row + 1 + i, 2, "%d", processes[i].pid);
        mvprintw(start_row + 1 + i, 12, "%s", processes[i].name.c_str());
    }
}


/* Initialize ncurses UI */
void init_ui()
{
    initscr();
    noecho();
    curs_set(0);
    nodelay(stdscr, TRUE);

    start_color();

    init_pair(1, COLOR_GREEN, COLOR_BLACK);
    init_pair(2, COLOR_CYAN, COLOR_BLACK);
}


/* Draw main UI screen */
void draw_ui(double cpu, double memory, const std::vector<Process>& processes)
{
    clear();

    attron(COLOR_PAIR(1) | A_BOLD);
    mvprintw(1, 2, "SYSTEM RESOURCE MONITOR");
    attroff(COLOR_PAIR(1) | A_BOLD);

    attron(COLOR_PAIR(2));
    mvprintw(3, 2, "CPU Usage   : ");
    draw_bar(3, 16, cpu, 40);

    mvprintw(5, 2, "Memory Usage: ");
    draw_bar(5, 16, memory, 40);
    attroff(COLOR_PAIR(2));

    draw_process_table(8, processes);

    mvprintw(25, 2, "Press 'q' to quit");

    refresh();
}


/* Close ncurses */
void close_ui()
{
    endwin();
}