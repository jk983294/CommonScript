#!/bin/bash

# (()) for numeric test, ( -lt -le -eq -ne -ge -gt)
# [[]] for string test, ( > < = )

# [[ -f "somefile" ]]           check if file
# [[ ! -f "somefile" ]]         check if not file
# [[ -n "$var" ]]               check if var is null
# [[ "$a" = "$b" ]]             check if $a == $b
# -r file                       check read permission
# -w file                       check write permission
# -x file                       check execute permission
# -f file                       check if file
# -d file                       check if directory
# -c file                       check if special character file
# -b file                       check if special block file
# -s file                       check if file size > 0
# -t file                       check if tty

if (( $# < 1 )); then
    echo "usage: $0 <name>"
    exit 1
fi

if [[ $1 = "if" ]]; then
    echo "if"
elif [[ $1 = "elseif" ]]; then
    echo "elseif"
else
    echo "else"
fi

echo "hello $1"
exit 0
