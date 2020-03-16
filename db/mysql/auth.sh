# check plugin
mysql> SELECT User, Host, plugin FROM mysql.user;

# change it from auth_socket to mysql_native_password
mysql> USE mysql;
mysql> UPDATE user SET plugin='mysql_native_password' WHERE User='root';
mysql> FLUSH PRIVILEGES;
mysql> exit;

# add another user
mysql> USE mysql;
mysql> CREATE USER 'kun'@'localhost' IDENTIFIED BY '123456';
mysql> GRANT ALL PRIVILEGES ON *.* TO 'kun'@'localhost';
mysql> UPDATE user SET plugin='mysql_native_password' WHERE User='kun';
mysql> FLUSH PRIVILEGES;
mysql> exit;

# password policy level
mysql> SET GLOBAL validate_password_policy=LOW;
mysql> SET GLOBAL validate_password_length = 6;
mysql> SET GLOBAL validate_password_number_count = 0;

$ sudo service mysql stop
$ sudo service mysql start
$ mysql_secure_installation # reset password of root

# edit 
vim /etc/mysql/mysql.conf.d/mysqld.cnf
skip-grant-tables           # add this line to [mysqld] session 