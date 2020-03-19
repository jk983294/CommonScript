# systemd / journald

# view log
journalctl
journalctl -k                                   # show kernel, also found in dmesg
journalctl -n
journalctl -n 20                                # show recent logs
journalctl -f                                   # follow

# filter log by time
journalctl -b                                   # display from the curret boot
journalctl --list-boots                         # list boots
journalctl -b -1                                # show by boot index (from -list-boots)
journalctl -b 5369647fabcc452c96aa6be93142cadf  # show by boot id (from -list-boots)
journalctl --since "2020-03-16 11:20:00"
journalctl --since "2020-03-16 11:20:00" --until "2020-03-16 11:22:00"
journalctl --since yesterday
journalctl --since today
journalctl --since "2020-03-16 11:20:00" --until "1 minute ago"

# filter log by content
journalctl -u nginx.service --since today       # by unit
journalctl _PID=2218                            # by pid
id -u kun                                       # show user id
journalctl _UID=1000 --since today              # by user id
man systemd.journal-fields                      # check all available fields
journalctl -F _UID                              # show uid recorded by journal
journalctl /usr/bin/code                        # by binary

# filter by priority (emerg/alert/crit/err/warning/notice/info/debug)
journalctl -p err -b

# maintenance
journalctl --disk-usage                         # display disk used by log
journalctl --vacuum-size=1G                     # shrink log by size
journalctl --vacuum-time=1years                 # shrink log by time

# limit log expansion, edit config (SystemMaxUse/SystemKeepFree/SystemMaxFileUse)
vim /etc/systemd/journald.conf

# view log in local timezone
timedatectl list-timezones                      # find available timezone like Asia/Shanghai
timedatectl set-timezone Asia/Shanghai
timedatectl status
