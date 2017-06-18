#!/bin/bash

sudo apt-get install mongodb

sudo service mongodb stop
sudo service mongodb start

# after change conf, locatrion of database
vim /etc/mongodb.conf
rm /var/lib/mongodb/mongod.lock
mongod -repair
chown mongodb /home/kun/Data/mongo
chgrp mongodb /home/kun/Data/mongo

# test
mongo
