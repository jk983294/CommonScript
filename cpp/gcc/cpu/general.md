### Absolute Priority
higher absolute priority than any other process doesn’t guarantee the process can run continuously. 

Two things that can wreck a good CPU run are interrupts and page faults.

To neutralize page faults threat, use mlock or mlockall

### scheduling policy
* SCHED_OTHER Traditional Scheduling
* SCHED_FIFO First In First Out
* SCHED_RR Round Robin

### api
```c++
int sched_setscheduler (pid t pid, int policy, const struct sched_param *param);
int sched_getscheduler (pid t pid);
int sched_setparam (pid t pid, const struct sched_param *param);
int sched_getparam (pid t pid, struct sched_param *param);
int sched_get_priority_min (int policy);    // returns the lowest absolute priority value that is allowable for a process with scheduling policy policy
int sched_get_priority_max (int policy);
int sched_rr_get_interval (pid t pid, struct timespec *interval);   // returns time slice used with the Round Robin scheduling policy, usually 150 microseconds defined in Linux kernel
int sched_yield (void);     // voluntarily gives up the process' claim on the CPU
```

### Traditional Scheduling
dynamic priority is a combination of these things, but mostly it is just determines the length of the time slice.

nice value is an integer, usually in the range -20 to 20, and represents an upper limit on a process' dynamic priority. The higher the nice number, the lower that limit. a process with a nice value of 20 can get only 10 milliseconds on the CPU at a time, whereas a process with a nice value of -20 can achieve a high enough priority to get 400 milliseconds.

### api for Traditional Scheduling
declared in sys/resource.h, api's priority means nice value actually

PRIO_MIN The lowest valid nice value

PRIO_MAX The highest valid nice value

```c++
int getpriority (int class, int id)
int setpriority (int class, int id, int niceval)
int nice (int increment)
```

### cpu affinity
The scheduler will schedule the thread or process on CPUs specified by the affinity masks.

```c++
void CPU_ZERO (cpu_set_t *set)
void CPU_SET (int cpu, cpu_set_t *set)
void CPU_CLR (int cpu, cpu_set_t *set)
int CPU_ISSET (int cpu, const cpu_set_t *set)
int sched_getaffinity (pid t pid, size t cpusetsize, cpu_set_t *cpuset)
int sched_setaffinity (pid t pid, size t cpusetsize, const cpu_set_t *cpuset)
```

### processor
```c++
int get_nprocs_conf (void)  # the number of processors the operating system configured
int get_nprocs (void)       # the number of available processors
```
