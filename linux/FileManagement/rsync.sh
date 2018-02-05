#!/usr/bin/env bash

# rsync
# a for archive mode, preserve permission
# v for verbose mode
# /home/ means all content of home folder but exclude the folder itself
# /home means all content of home folder and include the folder itself
rsync -av /home/ /backup/           # default sync not include deletion of source folder
rsync -av --delete /home/ /backup/  # sync the deletion of source folder
rsync -avz kun@192.168.31.118:/home/kun/Downloads/ /home/jk/Downloads/  # copy remote data to local directory
