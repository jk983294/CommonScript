# check target host port open
# start -> control panel -> programs -> turn windows features on or off, choose check telnet client
telnet host port
# connection refused means nothing is running on that port
# accepted means that something is running on that port
# timeout means that a firewall is blocking access


# lookup ip for target website
 nslookup stackoverflow.com 223.5.5.5
 # add into hosts
 151.101.129.69      stackoverflow.com
 # flush dns
 ipconfig /flushdns
