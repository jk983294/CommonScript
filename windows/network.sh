# check target host port open
# start -> control panel -> programs -> turn windows features on or off, choose check telnet client
telnet host port
# connection refused means nothing is running on that port
# accepted means that something is running on that port
# timeout means that a firewall is blocking access
