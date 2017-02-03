#!/usr/bin/env bash

# count and print matched pattern
awk '/a/{++cnt} END {print "Count = ", cnt}' score.txt