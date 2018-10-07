# install
sudo apt update
sudo apt install nginx

# adjust firewall
sudo ufw app list

# control app
systemctl status nginx
systemctl start nginx
systemctl enable nginx
systemctl restart nginx

# nginx command
/usr/sbin/nginx
nginx -v
nginx -t                                    # check config ok
nginx -s reload                             # load latest config
nginx -s stop                               # stop immediately
nginx -s quit                               # stop gracefully, finish all existing request
nginx -s reopen                             # reopen log

# check if service up
http://localhost/                           # default page is /usr/share/nginx/html/index.html

# put web under
/var/www/html

# conf under
vim /etc/nginx/nginx.conf

# related decectory
/etc/logrotate.d/nginx
/etc/ufw/applications.d/nginx
/etc/nginx
/etc/default/nginx
/etc/init.d/nginx
/usr/share/nginx
/usr/share/doc/nginx
/usr/sbin/nginx
/usr/lib/nginx
/var/log/nginx
/var/lib/nginx

# enable php
apt-get install php-fpm
vim /etc/php/7.2/fpm/php.ini
systemctl status php7.2-fpm
sudo systemctl restart php7.2-fpm
vim /etc/nginx/sites-enabled/default                    # enable php
