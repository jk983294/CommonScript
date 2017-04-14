#!/bin/bash

# copy file from B to A while logged into B
scp /path/to/src username@A:/path/to/dest

# copy file from A to B while logged into A
scp username@B:/path/to/src /path/to/dest
