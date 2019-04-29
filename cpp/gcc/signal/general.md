### signal overview
event category: errors, external events, and explicit requests.

SIGKILL and SIGSTOP can be ignored

### signal state
pending, delivered, blocked, unblocked

while the handler is running, that particular signal is normally blocked. 

However, your handler can still be interrupted by delivery of another kind of signal. To avoid this, you can use the sa_mask member of the action structure passed to sigaction to explicitly specify which signals should be blocked while the signal handler runs.

### signal produce
ctrl + c -> SIGINT

ctrl + z -> SIGTSTP

kill -USR2 pid

```c++
int raise (int signum);      // raise to the calling process
int kill (pid t pid, int signum);    // send signal to other process
```

### signal explain
SIGBUS often result from dereferencing a misaligned pointer, such as referring to a four-word integer at an address not divisible by four

### signal handler
they can be called asynchronously. That is, a handler might be called at any point in the program, unpredictably

If two signals arrive during a very short interval, one handler can run within another.

The best practice is to write a handler that does nothing but set an external variable that the program checks regularly, and leave all serious work to the program.

### atomic access
sig_atomic_t, Reading and writing this data type is guaranteed to happen in a single instruction

In practice, you can assume that int is atomic. You can also assume that pointer types are atomic; that is very convenient

a flag which is set by the handler, and tested and cleared by the main program from time to time, is always safe even if access actually requires two instructions

### Primitives Interrupted by Signals
A signal can arrive and be handled while an I/O primitive such as open or read is waiting for an I/O device.

POSIX make the primitive fail right away. The error code for this kind of failure is EINTR.

Typically, POSIX applications that use signal handlers must check for EINTR after each library function that can return it, in order to try the call again.

BSD avoids EINTR entirely, restart the interrupted primitive, instead of making it fail.

If you specify the SA_RESTART flag, return from that handler will resume a primitive; otherwise, return from that handler will cause EINTR.

The default choice depends on the feature test macros (_BSD_SOURCE or _GNU_SOURCE) before calling signal

### signal blocking
sigprocmask or sa_mask in sigaction call
```c++
// Signal Sets
int sigemptyset (sigset t *set);    // exclude all of the defined signals
int sigfillset (sigset t *set);     // include all of the defined signals
int sigaddset (sigset t *set, int signum);  // adds the signal signum to the signal set
int sigdelset (sigset t *set, int signum);  // removes the signal signum from the signal set
int sigismember (const sigset t *set, int signum);  // tests whether the signal signum is a member of the signal set

// Signal Mask
int sigprocmask (int how, const sigset_t *restrict set, sigset_t *restrict oldset);
```

### wait for  signal
Note that pause can conceal serious timing errors that can make a program hang mysteriously.
```c++
int pause (void);   // wait all signals
int sigsuspend (const sigset t *set);  // program suspended until one signal that is not a member of set arrives
```

### merged signal
If multiple signals of the same type are delivered to your process before your signal handler has a chance to be invoked at all, the handler may only be invoked once, as if only a single signal had arrived
