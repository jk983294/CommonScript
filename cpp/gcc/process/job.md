### overview
Job control refers to the protocol for allowing a user to move between multiple process groups (or jobs) within a single login session.

A session is a larger group of processes.


```c++
pid_t setsid (void);    // creates a new session
pid_t getsid (pid t pid); // returns the process group ID of the session leader of the specified process
pid_t getpgrp (void); // returns the process group ID of the calling process
pid_t getpgrp (pid t pid); // returns the process group ID of the process pid
int setpgid (pid t pid, pid t pgid); // puts the process pid into the process group pgid
```


