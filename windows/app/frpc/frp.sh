# server做成开机服务
cp frps /usr/bin/
mkdir /etc/frp
cp frps.ini /etc/frp/
mkdir /var/frp
vim /etc/frp/frps.ini
#log_file = /var/frp/frps.log
#log_level = info
#log_max_days = 3
#token = 12345678
cp systemd/frps.service /etc/systemd/system/
systemctl start frps
systemctl status frps
systemctl enable frps

# 客户端
vim frpc.ini
nohup /opt/frp/frpc -c /opt/frp/frpc.ini &
