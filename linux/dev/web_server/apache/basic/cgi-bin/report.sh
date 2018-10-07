#!/bin/bash

echo 'Content-type: text/html'
echo ''
echo "<h1>$(uname -n)</h1>"
echo "<h2>Root Filesystem</h2>"
echo "`df -hT / | grep -v Filesystem`"
