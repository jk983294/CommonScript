#!/bin/bash

exec 1>test.out
exec 2>test.error

echo "this is a test of redirecting all output"
echo "from a script to another file"
echo "without having to redirect every individual line"
