#!/bin/bash

sudo add-apt-repository ppa:hoytech/vmtouch
sudo apt-get update
sudo apt-get install vmtouch

# how much of the /bin/ directory is currently in cach
vmtouch /bin/

# how much of big-dataset.txt is currently in memory
vmtouch -v big-dataset.txt

# bring it into memory
vmtouch -vt big-dataset.txt

# evict a.txt from memory, making room for others
vmtouch -ve a.txt

# daemonise and lock all files in a directory into physical memory
vmtouch -dl /var/www/htdocs/critical/
