#!/usr/bin/awk

# built-in function
awk 'BEGIN { PI = 3.14159265; x = -10; y = 10; result = atan2 (y,x) * 180 / PI; printf "result: %f \n", result}'
awk 'BEGIN { PI = 3.14159265; x = -10; y = 10; result = cos(x * PI / 180.0); printf "result: %f \n", result}'
awk 'BEGIN { PI = 3.14159265; x = -10; y = 10; result = sin(x * PI / 180.0); printf "result: %f \n", result}'
awk 'BEGIN { y = 10; result = exp(y); printf "result: %f \n", result}'
awk 'BEGIN { y = 10; result = sqrt(y); printf "result: %f \n", result}'
awk 'BEGIN { param = 5.12345; result = int(param); printf "result: %f \n", result}'
awk 'BEGIN { param = 5.5; result = log(param); printf "result: %f \n", result}'
awk 'BEGIN { print "Random num1 =" , rand()}'
awk 'BEGIN { param = 10; print "Random num1 =" , srand(); printf "srand(%d) = %d\n", param, srand(param)}'
# built-in string function
awk 'BEGIN { arr[0] = "Three"; arr[1] = "One"; arr[2] = "Two"; asort(arr); for (i in arr) printf "arr[%d] = %s\n", i, arr[i] }'
awk 'BEGIN { arr["Two"] = 1; arr["One"] = 2; arr["Three"] = 3; asorti(arr); for (i in arr) printf "%s\n", arr[i] }'
awk 'BEGIN { str = "Hello, World World"; print "before  = " str; gsub("World", "Jerry", str); print "after = " str}'
awk 'BEGIN { str = "Hello, World World"; print "before  = " str; sub("World", "Jerry", str); print "after = " str}'
awk 'BEGIN { str = "One Two Three"; subs = "Two"; ret = index(str, subs); printf "Substring \"%s\" found at %d location.\n", subs, ret }'
awk 'BEGIN { str = "Hello, World !!!"; print "Length = ", length(str) }'
awk 'length($0) > 18' score.txt
awk 'BEGIN { str = "One Two Three";subs = "Two"; ret = match(str, subs); printf "Substring \"%s\" found at %d location.\n", subs, ret }'
awk 'BEGIN { str = "One,Two,Three,Four"; split(str, arr, ","); print "Array contains following values"; for (i in arr) print arr[i] }'
awk 'BEGIN { str = sprintf("%s", "Hello, World !!!"); print str }'
awk 'BEGIN { print "Decimal num = " strtonum("123"); print "Octal num = " strtonum("0123"); print "Hexadecimal num = " strtonum("0x123") }'
awk 'BEGIN { str = "Hello, World !!!"; subs = substr(str, 1, 5); print "Substring = " subs }'
awk 'BEGIN { str = "HELLO, WORLD !!!"; print "Lowercase string = " tolower(str) }'
awk 'BEGIN { str = "hello, world !!!"; print "Lowercase string = " toupper(str) }'
# built-in time function
awk 'BEGIN { print "Number of seconds since the Epoch = " systime() }'
awk 'BEGIN { print "Number of seconds since the Epoch = " mktime("2016 3 7 30 20 10") }'
awk 'BEGIN { print strftime("Time = %m/%d/%Y %H:%M:%S", systime()) }'
# Miscellaneous Functions
awk '{getline; print $0}' score.txt
awk 'BEGIN { ret = system("date"); print "Return value = " ret }'
