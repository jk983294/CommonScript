### overview
* a daemon called “Syslogd” Syslogd listens for messages on a Unix domain socket named /dev/log
* It listens on the syslog UDP port as well as the local socket for messages
* Syslog can handle messages from the kernel itself, another daemon (sometimes called “Klogd”) extracts messages from the kernel and passes them on to Syslog
* configuration file (usually /etc/syslog.conf), Syslogd routes messages in various ways:
1. Write to the system console
2. Mail to a specific user
3. Write to a log file
4. Pass to another daemon
5. Discard

### message
provide two pieces of classification information
* facility: this identifies who submitted the message.
* priority: this tells how important the content of the message is.

### api
in syslog.h

```c++
void openlog (const char *ident, int option, int facility)
void syslog (int facility_priority, const char *format, ... )
void closelog (void)
```
