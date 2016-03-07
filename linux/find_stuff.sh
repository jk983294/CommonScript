#! /usr/bin/awk
which awk
awk --help
# create a text command.awk file containing AWK command like {print}
awk -f command.awk marks.txt
# -v option assigns a value to variable
awk -v name=Jerry 'BEGIN{printf "Name = %s\n", name}'
# --dump-variables[=file] option prints a sorted list of global variables and their final values to file. The default file is awkvars.out.
awk --dump-variables ''

# Regular Expression Operators
# ~ looks for a field that contains the match string.
awk '$0 ~ 9' marks.txt
awk '$0 !~ 9' marks.txt

# Regular Expressions
# Dot matches any single character except end of line character.
echo -e "cat\nbat\nfun\nfin\nfan" | awk '/f.n/'
# Start of line
echo -e "This\nThat\nThere\nTheir\nthese" | awk '/^The/'
# End of line
echo -e "knife\nknow\nfun\nfin\nfan\nnine" | awk '/n$/'
# Match character set
echo -e "Call\nTall\nBall" | awk '/[CT]all/'
# Exclusive set
echo -e "Call\nTall\nBall" | awk '/[^CT]all/'
# Alteration
echo -e "Call\nTall\nBall\nSmall\nShall" | awk '/Call|Ball/'
# Zero or one occurrence
echo -e "Colour\nColor" | awk '/Colou?r/'
# Zero or more occurrence
echo -e "ca\ncat\ncatt" | awk '/cat*/'
# One or more occurrence
echo -e "111\n22\n123\n234\n456\n222"  | awk '/2+/'
# Grouping
echo -e "Apple Juice\nApple Pie\nApple Tart\nApple Cake" | awk '/Apple (Juice|Cake)/'

# display all content
awk '{print}' marks.txt 
awk '{print $0}' marks.txt 
# add header and print all file
awk 'BEGIN{printf "Sr No\tName\tSub\tMarks\n"} {print}' marks.txt
# print only certain columns based on 1 not 0, $0 means whole line
awk '{print $3 "\t" $4}' marks.txt
# prints all the lines that match pattern /a/.
awk '/a/ {print $0}' marks.txt

# count and print matched pattern
awk '/a/{++cnt} END {print "Count = ", cnt}' marks.txt

# Operators
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
awk 'length($0) > 18' marks.txt
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
awk '{getline; print $0}' marks.txt
awk 'BEGIN { ret = system("date"); print "Return value = " ret }'

# Arrays
awk 'BEGIN { arr[0] = 1; arr[1] = 2; arr[2] = 3; for (i in arr) printf "arr[%d] = %d\n", i, arr[i] }'
awk 'BEGIN { fruits["mango"]="yellow"; fruits["orange"]="orange"; print fruits["orange"] "\n" fruits["mango"]}'
awk 'BEGIN { fruits["mango"]="yellow"; fruits["orange"]="orange"; delete fruits["orange"]; print fruits["orange"]}'
awk 'BEGIN { array["0,0"] = 100; array["0,1"] = 200; array["1,0"] = 400; array["1,1"] = 500; print "array[0,0] = " array["0,0"]; }'

# Control Flow
awk 'BEGIN {num = 10; if (num % 2 == 0) printf "%d is even number.\n", num }'
awk 'BEGIN {num = 11; if (num % 2 == 0) printf "%d is even number.\n", num; else printf "%d is odd number.\n", num }'
awk 'BEGIN { a=30; if (a==10) print "a = 10"; else if (a == 20) print "a = 20"; else if (a == 30) print "a = 30"; }'
awk 'BEGIN { for (i = 1; i <= 5; ++i) print i }'
awk 'BEGIN {i = 1; while (i < 6) { print i; ++i } }'
awk 'BEGIN {i = 1; do { print i; ++i } while (i < 6) }'
awk 'BEGIN {sum = 0; for (i = 0; i < 20; ++i) { sum += i; if (sum > 50) break; else print "Sum =", sum } }'
awk 'BEGIN {for (i = 1; i <= 20; ++i) {if (i % 2 == 0) print i ; else continue} }'
awk 'BEGIN {sum = 0; for (i = 0; i < 20; ++i) { sum += i; if (sum > 50) exit(10); else print "Sum =", sum } }'
awk '{if ($0 ~/Shyam/) next; print $0}' marks.txt

# User Defined Functions
awk 'function addition(num1, num2){ result = num1 + num2; return result; } BEGIN { res = addition(10, 20); print "10 + 20 = " res; }'

# Output Redirection  >> is append, > is create new file then append
awk 'BEGIN { print "Hello, World !!!" > "message.txt" }'
awk 'BEGIN { print "Hello, World !!!" >> "/tmp/message.txt" }'
awk 'BEGIN { print "hello, world !!!" | "tr [a-z] [A-Z]" }'
BEGIN {
	cmd = "tr [a-z] [A-Z]"
	print "hello, world !!!" |& cmd
	close(cmd, "to")
	cmd |& getline out
	print out;
	close(cmd);
}

# Pretty Printing
awk 'BEGIN { printf "Sr No\vName\vSub\vMarks\n" }'
awk 'BEGIN { printf "Field 1\bField 2\bField 3\bField 4\n" }'
awk 'BEGIN { printf "ASCII value 65 = character %c\n", 65 }'
awk 'BEGIN { printf "Percentags = %d\n", 80.66 }'
awk 'BEGIN { printf "Percentags = %E\n", 80.66 }'
awk 'BEGIN { printf "Percentags = %f\n", 80.66 }'
awk 'BEGIN { printf "Percentags = %g\n", 80.66 }'
awk 'BEGIN { printf "Percentags = %d%%\n", 80.66 }'
awk 'BEGIN { num1 = -10; num2 = 20; printf "Num1 = %+d\nNum2 = %+d\n", num1, num2 }'


# built in variables
# ARGC the number of arguments
awk 'BEGIN {print "Arguments =", ARGC}' One Two Three Four
# ARGV an array which stores the command-line arguments
awk 'BEGIN { for (i = 0; i < ARGC; ++i) { printf "ARGV[%d] = %s\n", i, ARGV[i] } }' one two three four
# CONVFMT represents the conversion format for numbers and its default value is %.6g.
awk 'BEGIN { print "Conversion Format =", CONVFMT }'
# OFMT represents output format number and its default value is %.6g.
awk 'BEGIN {print "OFMT = " OFMT}'
# ENVIRON is an associative array of environment variables.
awk 'BEGIN { print ENVIRON["USER"] }'
# FILENAME represents the current file name.
awk 'END {print FILENAME}' marks.txt
# FS represents the field separator and its default value is space.
awk 'BEGIN {print "FS = " FS}' | cat -vte
# OFS represents output field separator and its default value is space.
awk 'BEGIN {print "OFS = " OFS}' | cat -vte
# ORS represents output record separator and its default value is newline.
awk 'BEGIN {print "ORS = " ORS}' | cat -vte
# RS represents (input)record separator and its default value is newline.
awk 'BEGIN {print "RS = " RS}' | cat -vte
# SUBSEP represents separator character for array subscripts and its default value is \034.
awk 'BEGIN { print "SUBSEP = " SUBSEP }' | cat -vte
# NF represents the number of fields in current record.
# For instance below example prints only those lines which contains more than two fields.
echo -e "One Two\nOne Two Three\nOne Two Three Four" | awk 'NF > 2'
# NR represents the number of the current record.
# For instance below example prints first two records
echo -e "One Two\nOne Two Three\nOne Two Three Four\n one" | awk 'NR < 3'
# RLENGTH represents the length of the string matched by match function. AWK's match function searches for a given string in the input-string.
awk 'BEGIN { if (match("One Two Three", "One ")) { print RLENGTH } }'
# RSTART represents the first position in the string matched by match function.
awk 'BEGIN { if (match("One Two Three", "Thre")) { print RSTART } }'
# $0 represents the entire input record.
awk '{print $0}' marks.txt
# $n represents nth field in current record where fields are separated by FS.
awk '{print $3 "\t" $4}' marks.txt
# IGNORECASE When this variable is set GAWK becomes case insensitive.
awk 'BEGIN{IGNORECASE=1} /amit/' marks.txt
