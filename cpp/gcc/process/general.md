### creation
```c++
int system (const char *command);
pid_t fork (void);
int execv (const char *filename, char *const argv[]);
```

### Process Identification
```c++
pid_t getpid (void);
pid_t getppid (void);
```

### Process Completion
```c++
pid_t waitpid (pid_t pid, int *status-ptr, int options);
```

### Program Termination
Functions that were registered with the atexit or on_exit functions are called in the reverse order of their registration
```c++
int atexit (void (*function) (void));
int on_exit (void (*function)(int status, void *arg), void *arg);

void abort (void); // it does not execute cleanup functions registered with atexit, it raising a SIGABRT signal

void _exit (int status); // terminate with status, it does not execute cleanup functions registered with atexit
```

things happen when process terminates:
* All open file descriptors in the process are closed
* A process exit status is saved to be reported back to the parent process via wait or waitpid
* Any child processes of the process being terminated are assigned a new parent process
* A SIGCHLD signal is sent to the parent process
* If the process is a session leader that has a controlling terminal, then a SIGHUP signal is sent to each process in the foreground job, and the controlling terminal is disassociated from that session
* If termination of a process causes a process group to become orphaned, and any member of that process group is stopped, then a SIGHUP signal and a SIGCONT signal are sent to each process in the group


### env
```c++
char * getenv (const char *name);   // name is not defined, the value is a null pointer
char * secure_getenv (const char *name); // returns a null pointer if the environment is untrusted.
int putenv (char *string);  // 'name=value'
int setenv (const char *name, const char *value, int replace);
int unsetenv (const char *name);
int clearenv (void);    // removes all entries
```

### Auxiliary Vector
type argument should be one of the ‘AT_’ symbols defined in elf.h.

AT_HWCAP inquire about any instruction set extensions available at runtime
```c++
unsigned long int getauxval (unsigned long int type);
```
### System Calls
```c++
long int syscall (long int sysno, ... );

int rc = syscall(SYS_chmod, "/etc/passwd", 0444);
```

