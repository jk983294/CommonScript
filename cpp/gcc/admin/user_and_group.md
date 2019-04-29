### persona
The effective user and group IDs of a process collectively form its persona.

Each user name belongs to one default group and may also belong to any number of supplementary groups.

The more common case of changing persona is when an ordinary user program needs access to a resource that wouldn’t ordinarily be accessible to the user actually running it.

### User Accounting Database
it typically lives in /etc/utmp , /var/adm/utmp or /var/run/utmp

### reading persona
```c++
uid_t getuid (void);    // real user ID
gid_t getgid (void);    // real group ID
uid_t geteuid (void);   // effective user ID
gid_t getegid (void);   // effective group ID
int getgroups (int count, gid t *groups);  // inquire about the supplementary group IDs of the process
```

### setting persona
```c++
int seteuid (uid t neweuid);    // effective user ID
int setuid (uid t newuid);      // privileged, sets both the real and effective user ID
int setreuid (uid t ruid, uid t euid);  // sets the real user ID of the process to ruid and the effective user ID to euid.
int setegid (gid t newgid);     // effective group ID
int setgid (gid t newgid);      // both the real and effective group ID
int setregid (gid t rgid, gid t egid);  // set the real group ID of the process to rgid and the effective group ID to egid.
int setgroups (size t count, const gid t *groups);  // sets the process’s supplementary group IDs
int initgroups (const char *user, gid t group);
```

### Identifying Who Logged In
```c++
char* getlogin (void);     // a string containing the name of the user logged in
char* cuserid (char *string);  // a string containing a user name associated with the effective ID of the process
```


