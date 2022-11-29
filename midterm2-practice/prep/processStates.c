// What is running, blocked, or ready states and their transactions.

// running - a process is using cpu time
// blocked - a process is readu for I/O is finish
// ready - a process is waiting to use CPU and be scheduled by task scheduler

// Transaction 1 - a process needs I/O
// Transaction 2 - a process timesout
// Transcation 3 - scheduler selects process from ready queue
// Transaction 4 - process gets input