# squid web proxy
# squid need to access Internet, the internal hosts no need to access Internet directly, it can access via squid proxy
systemctl start squid
systemctl enable squid
systemctl status squid
systemctl restart squid

# setup http proxy in firefox
Http proxy: 192.168.xx.xx port: 3128
check Use this proxy for all protocols

# check proxy log
tail -f /var/log/squid/access.log

# authenticate
htpasswd -c /etc/squid/squid.users kun
