#!/bin/bash

sudo apt-get install mysql-server
sudo apt-get install mysql-client
sudo apt-get install libmysqlclient-dev
sudo apt-get install libmysqlcppconn-dev

sudo mysql_secure_installation                  # setup user/passwd

# check if mysql installed successfully
# tcp        0      0 localhost:mysql         *:*                     LISTEN      8075/mysqld
sudo netstat -tap | grep mysql
systemctl status mysql.service

# https://dev.mysql.com/downloads/workbench/


### change data directory
# Stop MySQL using the following command:
sudo /etc/init.d/mysql stop
# Copy the existing data directory (default located in /var/lib/mysql) using the following command:
sudo cp -R -p /var/lib/mysql /home/kun/lib/mysql
# edit the MySQL configuration file with the following command:
# Look for the entry for datadir, and change the path (which should be /var/lib/mysql) to the new data directory.
sudo vim /etc/mysql/my.cnf
# or perhaps
sudo vim /etc/mysql/mysql.conf.d/mysqld.cnf
# Look for lines beginning with /var/lib/mysql. Change /var/lib/mysql in the lines with the new path.
sudo vim /etc/apparmor.d/usr.sbin.mysqld
# edit if needed for /etc/apparmor.d/tunables/alias. content change: alias /var/lib/mysql/ -> /newpath/
sudo vim /etc/apparmor.d/tunables/alias
# Restart the AppArmor profiles with the command:
sudo /etc/init.d/apparmor reload
# Restart MySQL with the command:
sudo /etc/init.d/mysql restart
