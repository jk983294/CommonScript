#!/usr/bin/env bash

# = += -= *= /= %= ^= **=	                ��ֵ
# ?:	                                    C�������ʽ
# ||	                                    �߼���
# &&	                                    �߼���
# ~ ~!	                                    ƥ��������ʽ�Ͳ�ƥ��������ʽ
# < <= > >= != ==	                        ��ϵ�����
# space	                                    ����
# + -	                                    �ӣ���
# * / %	                                    �ˣ���������
# + - !	                                    һԪ�ӣ������߼���
# ^ ***	                                    ����
# ++ --	                                    ���ӻ���٣���Ϊǰ׺���׺
# $	                                        �ֶ�����
# in	                                    �����Ա

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