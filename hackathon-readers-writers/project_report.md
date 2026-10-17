# Project Report
## Readers–Writers Concurrent Database Simulator

### 1. Abstract
The Readers–Writers problem is a classical synchronization problem in operating systems. This project implements a concurrent database simulator in C using POSIX threads and read-write locks. Multiple readers can access shared data simultaneously, while writers receive exclusive access to modify it. Atomic counters are used to validate synchronization behavior. In the observed execution, the final database value was 140 and no synchronization violations were reported.

### 2. Introduction
Concurrent systems allow multiple threads to operate at the same time. When threads access shared data, improper synchronization can cause race conditions and inconsistent results. The Readers–Writers problem demonstrates how to coordinate shared reading and exclusive writing safely.

### 3. Problem Statement
Design a concurrent database simulation that permits multiple readers to read shared data while ensuring that only one writer modifies the database at a time, without readers accessing the database during a write.

### 4. Objectives
- Implement reader and writer threads using POSIX threads.
- Synchronize access using a read-write lock.
- Allow simultaneous reading when no writer holds the lock.
- Protect database updates from conflicting access.
- Validate the final database value and report synchronization violations.

### 5. Technologies Used
- Programming language: C
- Compiler: GCC
- Threading library: POSIX Threads (pthreads)
- Synchronization: POSIX read-write locks
- Atomic operations: C11 atomics
- Development environment: Ubuntu / WSL

### 6. System Design
The program initializes a shared database value to 100 and creates four reader threads and two writer threads. Each reader performs three read operations. Each writer performs two updates, adding 10 to the database per update.

Readers acquire a read lock, allowing other readers to access the shared value concurrently. Writers acquire a write lock, preventing other readers and writers from accessing the database during an update.

### 7. Implementation
The implementation uses `pthread_create()` to create threads and `pthread_join()` to wait for their completion. `pthread_rwlock_rdlock()` protects read operations, and `pthread_rwlock_wrlock()` protects write operations. Atomic counters track active readers, active writers, and detected synchronization violations.

### 8. Testing and Results
The program was compiled and executed successfully in Ubuntu/WSL.

- Initial database value: 100
- Reader threads: 4
- Writer threads: 2
- Updates per writer: 2
- Increment per update: 10
- Expected final value: 140
- Observed final value: 140
- Observed synchronization violations: 0
- Program status: PASSED

### 9. Applications
Readers–Writers synchronization concepts are relevant to shared databases, configuration stores, file systems, caching systems, and applications where reads are frequent and updates must be protected.

### 10. Limitations and Future Enhancements
The current project is a console-based simulation using an in-memory integer. Future enhancements could include configurable thread counts, repeated stress testing, timing measurements, starvation analysis, and a graphical visualization of thread activity.

### 11. Conclusion
The project demonstrates the use of concurrent threads and read-write locks to coordinate access to shared data. The observed run produced the expected final value and passed the implemented synchronization checks.

