# System log files are always located under the /var/log directory
apparmor/           # AppArmor log files
audit/              # Logs from the audit framework.
ConsoleKit/         # Logs of the ConsoleKit daemon (daemon for tracking what users are logged in and how they interact with the computer).
cups/               # Access and error logs of the Common Unix Printing System ( cups )
firewall/           # Firewall logs
gdm/                # Log files from the GNOME display manager
krb5/               # Log files from the Kerberos network authentication system.
lastlog             # A database containing information on the last login of each user. Use the command lastlog to view
localmessages       # Log messages of some boot scripts, for example the log of the DHCP client.
mail*               # Mail server ( postfix , sendmail ) logs.
messages            # default place where all kernel and system log messages go and should be the first place (along with /var/log/warn ) to look at in case of problems.
NetworkManager      # NetworkManager log files.
news/               # Log messages from a news server.
ntp                 # Logs from the Network Time Protocol daemon ( ntpd ).
pk_backend_zypp*    # PackageKit (with libzypp back-end) log files.
puppet/             # Log files from the data center automation tool puppet.
samba/              # Log files from Samba, the Windows SMB/CIFS file server.
warn                # Log of all system warnings and errors. This should be the first place (along with the output of the systemd journal) to look in case of problems.
wtmp                # Database of all login/logout activities, and remote connections. Use the command last to view. See man 1 last for more information
xinetd.log          # Log files from the extended Internet services daemon ( xinetd ).
Xorg.0.log          # X.Org start-up log file. Refer to this in case you have problems starting X.Org. Copies from previous X.Org starts are numbered Xorg. ? .log.
YaST2/              # All YaST log files.
zypp/               # libzypp log files. Refer to these files for the package installation history.
zypper.log          # Logs from the command line installer zypper


vim /etc/logrotate.conf     # edit it to make sure it will not increase too big