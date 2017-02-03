#!/usr/bin/env bash

# User Defined Functions
awk 'function addition(num1, num2){ result = num1 + num2; return result; } BEGIN { res = addition(10, 20); print "10 + 20 = " res; }'