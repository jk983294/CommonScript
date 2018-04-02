#!/usr/bin/env bash

# grep
# i             case insensitive
# v             reverse the search, display lines that do not match
# w             search for expression as a word, must has delimiter
# l             list names of files containing matching lines
# e             more than one expression ( pattern1 || pattern2 )
# E             enhanced complex expressions (egrep)
# n             show row number
# c             show match line count

# regular expression
# .                     any character
# *                     zero or more
# [abc] [a-z] [!a]
# ^ $                   anchor

grep Server /etc/ntp.conf                                   # search 'Server'
grep -i Server /etc/ntp.conf                                # search 'Server' in case insensitive mode
grep '\bserver\b' /etc/ntp.conf                             # search for word 'server' so that 'servers' won't show
grep '^server\b' /etc/ntp.conf                              # search for word 'server' which is start of line
grep '\bserver$' /etc/ntp.conf                              # search for word 'server' which is end of line
grep -ve'^#' -ve'^$' /etc/ntp.conf                          # don't show commented line and empty line
grep -E '[A-Z]{1,2}[0-9]{1,2}[A-Z]?\s[0-9][A-Z]{2}' a.txt   # search for postcode
grep -e pattern1 -e pattern2 file                           # pattern1 || pattern2
grep pattern1 file | grep pattern2                          # pattern1 && pattern2
grep -w word                                                # word must be delimitered by non-word constituent character
grep -nr pattern folder/*                                   # search pattern under folder recursively, show line number

grep [jk] file                                              # j or k

grep -A1 pattern                                            # 打印匹配行,再打印匹配行后1行
grep -B1 pattern                                            # 打印匹配行,再打印匹配行前1行
grep -C1 pattern                                            # 打印匹配行,再打印匹配行前后各自1行

# -o show only match, it means extract matched text
egrep -o ',e \w+ ,' data.txt | awk '{ print $2; }' | sort -u    # extract distinct exchange
