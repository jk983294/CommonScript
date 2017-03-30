#!/usr/bin/awk

awk '{print}' score.txt                                                     # display all content
awk '{print $0}' score.txt                                                  # display all content
awk 'BEGIN{printf "Sr No\tName\tSub\tMarks\n"} {print}' score.txt           # add header and print all file
awk '{print $3 "\t" $4}' score.txt                                          # print only certain columns based on 1 not 0, $0 means whole line
awk '/a/ {print $0}' score.txt                                              # prints all the lines that match pattern /a/.

# Pretty Printing
awk 'BEGIN { printf "Sr No\vName\vSub\vMarks\n" }'
awk 'BEGIN { printf "Field 1\bField 2\bField 3\bField 4\n" }'
awk 'BEGIN { printf "ASCII value 65 = character %c\n", 65 }'
awk 'BEGIN { printf "Percentages = %d\n", 80.66 }'
awk 'BEGIN { printf "Percentages = %E\n", 80.66 }'
awk 'BEGIN { printf "Percentages = %f\n", 80.66 }'
awk 'BEGIN { printf "Percentages = %g\n", 80.66 }'
awk 'BEGIN { printf "Percentages = %d%%\n", 80.66 }'
awk 'BEGIN { num1 = -10; num2 = 20; printf "Num1 = %+d\nNum2 = %+d\n", num1, num2 }'
