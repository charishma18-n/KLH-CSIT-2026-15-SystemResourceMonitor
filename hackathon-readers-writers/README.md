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

