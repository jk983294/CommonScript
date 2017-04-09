#!/bin/bash

# iterate
awk 'BEGIN { arr[0] = 1; arr[1] = 2; arr[2] = 3; for (i in arr) printf "arr[%d] = %d\n", i, arr[i] }'
awk 'BEGIN { fruits["mango"]="yellow"; fruits["orange"]="orange"; print fruits["orange"] "\n" fruits["mango"]}'

# delete
awk 'BEGIN { fruits["mango"]="yellow"; fruits["orange"]="orange"; delete fruits["orange"]; print fruits["orange"]}'

# multi-dimension array
awk 'BEGIN { array["0,0"] = 100; array["0,1"] = 200; array["1,0"] = 400; array["1,1"] = 500; print "array[0,0] = " array["0,0"]; }'
