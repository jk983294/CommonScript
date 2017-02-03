#!/usr/bin/env bash

# = += -= *= /= %= ^= **=	                赋值
# ?:	                                    C条件表达式
# ||	                                    逻辑或
# &&	                                    逻辑与
# ~ ~!	                                    匹配正则表达式和不匹配正则表达式
# < <= > >= != ==	                        关系运算符
# space	                                    连接
# + -	                                    加，减
# * / %	                                    乘，除与求余
# + - !	                                    一元加，减和逻辑非
# ^ ***	                                    求幂
# ++ --	                                    增加或减少，作为前缀或后缀
# $	                                        字段引用
# in	                                    数组成员

awk 'BEGIN { a = 50; b = 20; print "(a + b) = ", (a + b) }'
awk 'BEGIN { a = 50; b = 20; print "(a - b) = ", (a - b) }'
awk 'BEGIN { a = 50; b = 20; print "(a * b) = ", (a * b) }'
awk 'BEGIN { a = 50; b = 20; print "(a / b) = ", (a / b) }'
awk 'BEGIN { a = 50; b = 20; print "(a % b) = ", (a % b) }'
awk 'BEGIN { a = 10; a = a ^ 2; print "a =", a }'
awk 'BEGIN { a = 10; b = ++a; printf "a = %d, b = %d\n", a, b }'
awk 'BEGIN { a = 10; b = --a; printf "a = %d, b = %d\n", a, b }'
awk 'BEGIN { a = 10; b = a++; printf "a = %d, b = %d\n", a, b }'
awk 'BEGIN { a = 10; b = a--; printf "a = %d, b = %d\n", a, b }'
awk 'BEGIN { name = "Jerry"; print "My name is", name }'
awk 'BEGIN { cnt=10; cnt += 10; print "Counter =", cnt }'
awk 'BEGIN { cnt=100; cnt -= 10; print "Counter =", cnt }'
awk 'BEGIN { cnt=10; cnt *= 10; print "Counter =", cnt }'
awk 'BEGIN { cnt=100; cnt /= 5; print "Counter =", cnt }'
awk 'BEGIN { cnt=100; cnt %= 8; print "Counter =", cnt }'
awk 'BEGIN { cnt=2; cnt ^= 4; print "Counter =", cnt }'
awk 'BEGIN { cnt=2; cnt **= 4; print "Counter =", cnt }'
# Relational Operators
awk 'BEGIN { a = 10; b = 10; if (a == b) print "a == b" }'
awk 'BEGIN { a = 10; b = 20; if (a != b) print "a != b" }'
awk 'BEGIN { a = 10; b = 20; if (a < b) print "a < b" }'
awk 'BEGIN { a = 10; b = 10; if (a <= b) print "a <= b" }'
awk 'BEGIN { a = 10; b = 20; if (b > a ) print "b > a" }'
awk 'BEGIN { a = 10; b = 10; if (a >= b) print "a >= b" }'
# Logical Operators
awk 'BEGIN {num = 5; if (num >= 0 && num <= 7) printf "%d is in octal format\n", num }'
awk 'BEGIN {ch = "\n"; if (ch == " " || ch == "\t" || ch == "\n") print "Current character is whitespace." }'
awk 'BEGIN { name = ""; if (! length(name)) print "name is empty string." }'
# Ternary Operator
awk 'BEGIN { a = 10; b = 20; (a > b) ? max = a : max = b; print "Max =", max}'
# Unary Operators
awk 'BEGIN { a = -10; a = +a; print "a =", a }'
awk 'BEGIN { a = -10; a = -a; print "a =", a }'
# String concatenation operator
awk 'BEGIN { str1="Hello, "; str2="World"; str3 = str1 str2; print str3 }'