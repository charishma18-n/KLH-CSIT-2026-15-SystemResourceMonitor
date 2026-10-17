
# Test Cases — Readers-Writers Concurrent Database Simulator

## 1. Objective
To validate concurrent reader access, exclusive writer access, correct database updates, and synchronization safety.

## 2. Test Environment
- Operating System: Ubuntu Linux / WSL
- Language: C
- Compiler: GCC
- Concurrency Library: POSIX Threads (pthreads)
- Synchronization: POSIX read-write lock

## 3. Test Cases

| Test ID | Test Description | Expected Result |
|---|---|---|
| TC01 | Compile the source code | Compilation succeeds without errors |
| TC02 | Run four reader threads | Readers can access the database concurrently |
| TC03 | Run two writer threads | Writers update the database with exclusive access |
| TC04 | Verify database updates | Final value is 140 |
| TC05 | Check synchronization violations | Zero violations |
| TC06 | Verify final status | Program prints PASSED when validation succeeds |

## 4. Observed Results
During a successful execution:
- Initial database value: 100
- Number of readers: 4
- Number of writers: 2
- Updates per writer: 2
- Increment per update: 10
- Expected and observed final database value: 140
- Observed synchronization violations: 0
- Final status: PASSED

## 5. Conclusion
The observed run passed the implemented validation checks. The read-write lock protects database access, allowing concurrent readers while ensuring writers have exclusive access.
