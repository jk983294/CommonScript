#!/bin/bash

sleep 5
for SERVER in $INPUT_FEED_UPSTREAM;
do
    $ADMIN open_server $SERVER
done
