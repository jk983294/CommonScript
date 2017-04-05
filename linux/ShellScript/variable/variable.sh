#!/bin/bash

var1=10
var2=5
var3=$var1

ref1=`date +%y%m%d%H%M%S`
ref2=$(date +%y%m%d%H%M%S)

# [] operator, only support integer calculation
echo $[$var1 * ($var3 / $var2)]

# float calculation, precision controlled by scale
echo $(echo "scale=4; $var1 * ($var3 / $var2)" | bc)
result=$(bc << EOF
scale = 4
a1 = ($var3 / $var2)
b1 = ($var1 - $var2)
a1 + b1
EOF
)
echo $result

# expr must quote special character
echo $(expr $var1 '&' $var2)
echo $(expr $var1 '|' $var2)

echo $(expr $var1 + $var2)
echo $(expr $var1 - $var2)
echo $(expr $var1 '*' $var2)
echo $(expr $var1 / $var2)
echo $(expr $var1 % $var2)

echo $(expr $var1 '<' $var2)
echo $(expr $var1 '<=' $var2)
echo $(expr $var1 '>' $var2)
echo $(expr $var1 '>=' $var2)
echo $(expr $var1 = $var2)
echo $(expr $var1 != $var2)

if expr "$var1" '>' "$var2" >/dev/null
then
    echo "$var1"
else
    echo "$var2"
fi
