#!/usr/bin/awk

awk 'BEGIN {num = 10; if (num % 2 == 0) printf "%d is even number.\n", num }'
awk 'BEGIN {num = 11; if (num % 2 == 0) printf "%d is even number.\n", num; else printf "%d is odd number.\n", num }'
awk 'BEGIN { a=30; if (a==10) print "a = 10"; else if (a == 20) print "a = 20"; else if (a == 30) print "a = 30"; }'
awk 'BEGIN { for (i = 1; i <= 5; ++i) print i }'
awk 'BEGIN {i = 1; while (i < 6) { print i; ++i } }'
awk 'BEGIN {i = 1; do { print i; ++i } while (i < 6) }'
awk 'BEGIN {sum = 0; for (i = 0; i < 20; ++i) { sum += i; if (sum > 50) break; else print "Sum =", sum } }'
awk 'BEGIN {for (i = 1; i <= 20; ++i) {if (i % 2 == 0) print i ; else continue} }'
awk 'BEGIN {sum = 0; for (i = 0; i < 20; ++i) { sum += i; if (sum > 50) exit(10); else print "Sum =", sum } }'
awk '{if ($0 ~/Mike/) next; print $0}' score.txt
awk -F: '$1 ~ /kun/{print $1, $NF}' /etc/passwd
awk -F: '$1 !~ /kun/{print $1, $NF}' /etc/passwd
awk -F: '$1 == "kun"{print $1, $NF}' /etc/passwd
