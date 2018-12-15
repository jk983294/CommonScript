#!/bin/sh

python /home/kun/github/protoss/tool/PostServer.py 8024 &
python /home/kun/github/protoss/tool/PostServer.py 8025 &
python /home/kun/github/protoss/tool/PostServer.py 8026 &

# client test
python /home/kun/github/protoss/tool/PostClient.py 8023
