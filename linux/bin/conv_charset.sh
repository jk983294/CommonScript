#!/bin/bash

find . -type d -exec mkdir -p ../utf/{} \;
find . -type f -exec iconv -f GBK -t UTF-8 {} -o ../utf/{} \;
