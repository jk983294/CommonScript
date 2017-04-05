#!/bin/bash

exec 3>user.out

echo "this should display on the console"
echo "this should display in file" >&3
echo "this should display back on the console"
