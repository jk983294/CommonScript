### Host Identification
* host name, 'chicken'
* domain name, 'ai.mit.edu'
* Fully Qualified Domain Name (FQDN), 'chicken.ai.mit.edu'
* NIS (aka YP) name space

```c++
int gethostname (char *name, size t size);          // host name
int sethostname (const char *name, size t length);
int getdomainnname (char *name, size t length);     // NIS (aka YP) domain name
int setdomainname (const char *name, size t length);
long int gethostid (void);                          // primary Internet IP address of that machine, converted to a long int.
int sethostid (long int id)'
```

### Platform Type Identification
uname

sys/utsname.h

```c++
int uname (struct utsname *info); 
```

### Controlling and Querying Mount
/etc/fstab describes all possibly mounted filesystems

/etc/mtab or /var/run/mtab store the information about all the filesystems actually mounted

### System Parameters
in sys/sysctl.h
```c++
int sysctl (int *names, int nlen, void *oldval, size t *oldlenp, void* newval, size t newlen);
```

get info from proc file system
```c++
cat /proc/sys/vm/freepages      # display the free page thresholds
```
