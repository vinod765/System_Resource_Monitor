# System Resource Monitor (CLI Application)

## Overview

This project implements a **terminal-based system resource monitor** written in **C++**.
The application displays real-time system statistics such as CPU usage, memory consumption, and running processes directly inside the terminal.

The application refreshes periodically and provides a clean interface within the terminal environment.

---

# Features

### Core Features

* Real-time **CPU usage monitoring**
* **Memory usage monitoring**
* Display of **running processes**
* Periodic automatic refresh
* Terminal-based interface (no GUI)

### User Interface Features

* Terminal UI built using **ncurses**
* Smooth refresh with minimal flicker
* Colored terminal output
* CPU usage progress bar
* Memory usage progress bar

### Keyboard Interaction

* Press **q** to quit the monitor

---

# Technologies Used

* **C++**
* **ncurses** (for terminal UI)
* Linux **/proc filesystem**

System information is read directly from the Linux kernel through `/proc` files.

| File               | Purpose           |
| ------------------ | ----------------- |
| `/proc/stat`       | CPU statistics    |
| `/proc/meminfo`    | Memory statistics |
| `/proc/<pid>/comm` | Process names     |

This approach avoids high-level monitoring libraries and directly interfaces with the operating system.

---

# Project Structure

```
system-resource-monitor
│
├── README.md
│
└── src
    ├── main.cpp
    ├── cpu.cpp
    ├── cpu.h
    ├── memory.cpp
    ├── memory.h
    ├── process.cpp
    ├── process.h
    ├── ui.cpp
    └── ui.h
```

### Module Responsibilities

| Module  | Description                          |
| ------- | ------------------------------------ |
| cpu     | calculates CPU usage                 |
| memory  | calculates memory usage              |
| process | retrieves running processes          |
| ui      | handles terminal rendering           |
| main    | program entry point and refresh loop |

---

# How It Works

### CPU Usage

CPU statistics are read from:

```
/proc/stat
```

The program reads CPU counters twice with a short delay and calculates the percentage of active CPU time.

---

### Memory Usage

Memory statistics are obtained from:

```
/proc/meminfo
```

The program calculates used memory using:

```
Used Memory = MemTotal - MemAvailable
```

---

### Process Listing

Running processes are detected by scanning directories inside:

```
/proc
```

Each process directory contains metadata such as its name.

---

# Installation

This project is designed for **Linux systems**.

### Install Dependencies (Fedora)

```
sudo dnf install ncurses-devel
```

---

# Build Instructions

Compile the project using:

```
g++ src/*.cpp -lncurses -std=c++17 -o monitor
```

---

# Run the Program

```
./monitor
```

To exit the application press:

```
q
```

---

# Example Output

Example terminal interface:

```
SYSTEM RESOURCE MONITOR

CPU Usage   : [##############      ] 35%
Memory Usage: [################    ] 48%

PID        PROCESS
1          systemd
210        bash
912        chrome
1201       code
```

---

# Screenshots

Add screenshots of the running program in the repository.

Example location:

```
screenshots/monitor.png
```

---

# Design Decisions

### Modular Architecture

The system is divided into independent modules for CPU, memory, processes, and UI.
This improves maintainability and keeps the codebase organized.

---

### Direct Kernel Interface

The program reads system information directly from the Linux `/proc` filesystem rather than using high-level monitoring libraries.

This provides:

* better understanding of Linux internals
* fewer external dependencies
* improved performance

---

### Terminal UI Using ncurses

The `ncurses` library was used to create a responsive terminal interface with:

* colored text
* screen refresh control
* keyboard input handling

This allows smooth real-time updates without terminal flickering.

---

# Possible Improvements

Future enhancements may include:

* Process CPU usage statistics
* Memory usage per process
* Process sorting and filtering
* Scrollable process list
* Hierarchical process tree
* Interactive controls

---

 