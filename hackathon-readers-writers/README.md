# Readers–Writers Concurrent Database Simulator

## Overview
A C-based simulation of the classic Readers–Writers synchronization problem using POSIX threads and read-write locks.

## Features
- Multiple concurrent reader threads
- Writer threads with exclusive database access
- POSIX pthread read-write locks
- Atomic counters for synchronization validation
- Final database value and test status verification

## Technologies
- C
- POSIX Threads (pthreads)
- GCC
- Linux / Ubuntu / WSL
- Make

## Expected Result
The database starts at 100. Two writer threads each perform two updates of +10, so the expected final value is 140. The program reports synchronization violations and displays PASS or FAIL.

## Compilation and Execution
```bash
make
./build/readers_writers
```

## Project Purpose
To demonstrate process synchronization concepts, concurrent access, mutual exclusion, and safe database updates.
## Project Structure

```text
hackathon-readers-writers/
├── src/
│   └── main.c
├── tests/
│   └── test_cases.md
├── reports/
│   └── project_report.md
├── Makefile
└── README.md
```

## Build and Run

Requirements: GCC, Make, and POSIX Threads on Linux or Ubuntu/WSL.

Compile the program:

```bash
make
```

Run the simulator:

```bash
./build/readers_writers
```

Clean the compiled executable:

```bash
make clean
```

## Validation

The observed successful run produced:
- Final database value: 140
- Synchronization violations: 0
- Status: PASSED

## Team Contribution

This project was developed for an operating systems hackathon to demonstrate concurrency and synchronization using C and POSIX threads.

