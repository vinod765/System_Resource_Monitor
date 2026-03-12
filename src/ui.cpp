#include <ncursesw/ncurses.h>
#include <locale.h>
#include <vector>
#include <string>

#include "process.h"

using namespace std;


/* Draw bordered box */
void draw_box(int y, int x, int h, int w, const char* title)
{
    mvaddch(y,x,ACS_ULCORNER);
    mvaddch(y,x+w,ACS_URCORNER);
    mvaddch(y+h,x,ACS_LLCORNER);
    mvaddch(y+h,x+w,ACS_LRCORNER);

    mvhline(y,x+1,ACS_HLINE,w-1);
    mvhline(y+h,x+1,ACS_HLINE,w-1);

    mvvline(y+1,x,ACS_VLINE,h-1);
    mvvline(y+1,x+w,ACS_VLINE,h-1);

    mvprintw(y,x+2," %s ",title);
}


/* Draw usage bar */
void draw_bar(int row,int col,double percent,int width)
{
    int filled = (percent/100.0)*width;

    mvprintw(row,col,"[");

    for(int i=0;i<width;i++)
    {
        if(i < filled)
        {
            if(percent < 50)
                attron(COLOR_PAIR(1));
            else if(percent < 80)
                attron(COLOR_PAIR(2));
            else
                attron(COLOR_PAIR(3));

            addwstr(L"█");

            if(percent < 50)
                attroff(COLOR_PAIR(1));
            else if(percent < 80)
                attroff(COLOR_PAIR(2));
            else
                attroff(COLOR_PAIR(3));
        }
        else
        {
            addwstr(L"░");
        }
    }

    printw("] %.1f%%",percent);
}


/* Draw process table */
void draw_process_table(int start_row,const vector<Process>& processes)
{
    attron(A_BOLD);

    mvprintw(start_row,2,"PID");
    mvprintw(start_row,10,"NAME");
    mvprintw(start_row,40,"CPU %%");
    mvprintw(start_row,50,"MEM(MB)");

    attroff(A_BOLD);

    int max_rows = LINES - start_row - 4;

    for(int i=0;i<max_rows && i<processes.size();i++)
    {
        const Process& p = processes[i];

        mvprintw(start_row+1+i,2,"%6d",p.pid);
        mvprintw(start_row+1+i,10,"%-25s",p.name.c_str());
        mvprintw(start_row+1+i,40,"%6.2f",p.cpu);
        mvprintw(start_row+1+i,50,"%8.1f",p.memory);
    }
}


/* Initialize ncurses UI */
void init_ui()
{
    setlocale(LC_ALL,"");

    initscr();
    noecho();
    curs_set(0);

    keypad(stdscr,TRUE);

    timeout(1000);   // refresh every 1 second

    start_color();

    init_pair(1,COLOR_GREEN,COLOR_BLACK);
    init_pair(2,COLOR_YELLOW,COLOR_BLACK);
    init_pair(3,COLOR_RED,COLOR_BLACK);
}


/* Draw main dashboard */
void draw_ui(double cpu,double memory,const vector<Process>& processes)
{
    erase();

    int width = COLS-2;

    draw_box(0,0,6,width,"System Resource Monitor");

    mvprintw(2,3,"CPU Usage");
    draw_bar(2,15,cpu,40);

    mvprintw(4,3,"Memory Usage");
    draw_bar(4,15,memory,40);

    draw_box(7,0,LINES-10,width,"Processes");

    draw_process_table(9,processes);

    mvprintw(LINES-2,2,"Press 'q' to quit");

    wnoutrefresh(stdscr);
    doupdate();
}


/* Close UI */
void close_ui()
{
    endwin();
}