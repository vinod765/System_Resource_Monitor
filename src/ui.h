#ifndef UI_H
#define UI_H

#include <vector>
#include "process.h"

void init_ui();
void draw_ui(double cpu, double memory, const std::vector<Process>& processes);
void close_ui();

#endif