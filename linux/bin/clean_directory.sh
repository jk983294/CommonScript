#!/bin/bash

. log.sh
#
# clean up given directory, deleting all files older than the given number of days.
#
# usage: clean_directory.sh directory keep_days
#

if [[ -z $1 || -z $2 ]]
then
    log_die "usage: clean_directory  dir-path  days-to-keep\n"
else
    DIR=$1
    DAYS=$2
fi

if [[ ! -d $DIR ]]
then
    log_die "$DIR is not a directory\n"
fi

find $DIR -mindepth 1 -mtime +$DAYS -delete
