### overview
Name Service Switch (NSS)

The databases available in the NSS are
* aliases, Mail aliases
* ethers, Ethernet numbers
* group, Groups of users
* hosts, Host names and numbers
* netgroup, Network wide list of host and users
* networks, Network names and numbers
* protocols, Network protocols
* passwd, User passwords
* rpc, Remote procedure call names and numbers
* services, Network services
* shadow, Shadow user passwords

### config
config file: /etc/nsswitch.conf

services: files, db, dns, nis, and nisplus

On a system supporting shared libraries this is in fact a shared library with the name libnss_name.so.2.
