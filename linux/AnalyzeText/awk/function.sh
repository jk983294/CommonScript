#!/usr/bin/awk

# User Defined Functions
awk 'function addition(num1, num2){ result = num1 + num2; return result; } BEGIN { res = addition(10, 20); print "10 + 20 = " res; }'
awk 'function trim(str){ sub(/^[ \t\r\n]+/,"",str); sub(/[ \t\r\n]+$/,"", str);return str} BEGIN { print trim(" a "); }'
