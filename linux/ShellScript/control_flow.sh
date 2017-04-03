#!/bin/bash

# (()) for numeric test, ( -lt -le -eq -ne -ge -gt ++ -- ! ~ << >> & | && || **)
# [[]] for string test, ( > < = regex == )

# -r file                       check read permission
# -w file                       check write permission
# -x file                       check execute permission
# -f file                       check if file
# -d file                       check if directory
# -c file                       check if special character file
# -b file                       check if special block file
# -s file                       check if file size > 0
# -t file                       check if tty
# -e file                       check if file exist
# -O file                       check if exist and owned by current user
# -G file                       check if exist and owned by current user's group
# file1 -nt file2               check if file1 newer than file2
# file1 -ot file2               check if file1 older than file2

# check file
var3='/usr/bin/test'
var4='/bin/ls'
[[ -f $var3 ]] && (echo true) || (echo false)                                   # true
[[ ! -f $var3 ]] && (echo true) || (echo false)                                 # false
[[ -r $var3 ]] && (echo true) || (echo false)                                   # true
[[ -w $var3 ]] && (echo true) || (echo false)                                   # false
[[ -x $var3 ]] && (echo true) || (echo false)                                   # true
[[ -d $var3 ]] && (echo true) || (echo false)                                   # false
[[ -c $var3 ]] && (echo true) || (echo false)                                   # false
[[ -b $var3 ]] && (echo true) || (echo false)                                   # false
[[ -s $var3 ]] && (echo true) || (echo false)                                   # true
[[ -t $var3 ]] && (echo true) || (echo false)                                   # false
[[ -e $var3 ]] && (echo true) || (echo false)                                   # true
[[ -O $var3 ]] && (echo true) || (echo false)                                   # false
[[ -G $var3 ]] && (echo true) || (echo false)                                   # false
[[ $var3 -nt $var4 ]] && (echo true) || (echo false)                            # false
[[ $var3 -ot $var4 ]] && (echo true) || (echo false)                            # false

# [[]] string comparison
var1="hello"
[[ $var1 = "hello" ]] && (echo true) || (echo false)
[[ $var1 < "zello" ]] && (echo true) || (echo false)
[[ $var1 > "aello" ]] && (echo true) || (echo false)
[[ -n $var1 ]] && (echo 'length is not zero') || (echo 'length is zero')
[[ -z $var1 ]] && (echo 'length is zero') || (echo 'length is not zero')
[[ $var1 == "he" ]] && (echo true) || (echo false)

# test is equal to [] operator, argument must be integer
var2=10
(test $var2) && (echo true) || (echo false)                                     # return 0, i.e. true if var has content
(test $var2 -eq 10) && (echo true) || (echo false)
(test $var2 -ne 20) && (echo true) || (echo false)
(test $var2 -gt 5) && (echo true) || (echo false)
(test $var2 -lt 15) && (echo true) || (echo false)
(test $var2 -ge 10) && (echo true) || (echo false)
(test $var2 -le 10) && (echo true) || (echo false)

[[ $var2 ]] && (echo true) || (echo false)                                      # return 0, i.e. true if var has content
[[ $var2 -eq 10 ]] && (echo true) || (echo false)
[[ $var2 -ne 20 ]] && (echo true) || (echo false)
[[ $var2 -gt 5 ]] && (echo true) || (echo false)
[[ $var2 -lt 15 ]] && (echo true) || (echo false)
[[ $var2 -ge 10 ]] && (echo true) || (echo false)
[[ $var2 -le 10 ]] && (echo true) || (echo false)

# group condition
if [[ $var2 -eq 10 ]] && [[ $var2 -ne 20 ]]
then
    echo "true"
fi

# high feature of (())
if (( $var2 ** 2 > 10 )); then
    (( var2 = $var2 ** 2 ))
    echo "now var2 is $var2"
fi

# high feature of [[]]
if [[ $var1 == h* ]]; then
    echo "$var1 matches pattern ^h*o$"
fi

# use arguments
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
