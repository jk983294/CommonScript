#!/usr/bin/env bash

# internal variables
# \$n	                            当前记录的第n个字段，字段间由FS分隔
# \$0	                            完整的输入记录
# ARGC	                            命令行参数的数目
# ARGIND	                        命令行中当前文件的位置(从0开始算)
# ARGV	                            包含命令行参数的数组
# CONVFMT	                        数字转换格式(默认值为%.6g)ENVIRON环境变量关联数组
# ERRNO	                            最后一个系统错误的描述
# FIELDWIDTHS	                    字段宽度列表(用空格键分隔)
# FILENAME	                        当前文件名
# FNR	                            同NR，但相对于当前文件, if multiply file, it will be reset for each file
# FS	                            字段分隔符(默认是任何空格)
# IGNORECASE	                    如果为真，则进行忽略大小写的匹配
# NF	                            当前记录中的字段数
# NR	                            当前记录数
# OFMT	                            数字的输出格式(默认值是%.6g)
# OFS	                            输出字段分隔符(默认值是一个空格)
# ORS	                            输出记录分隔符(默认值是一个换行符)
# RLENGTH	                        由match函数所匹配的字符串的长度
# RS	                            记录分隔符(默认是一个换行符)
# RSTART	                        由match函数所匹配的字符串的第一个位置
# SUBSEP	                        数组下标分隔符(默认值是/034)
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
awk 'END {print FILENAME}' score.txt
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
echo -e "One Two\nOne Two Three\nOne Two Three Four" | awk '{print $NF}'        # print last field
# NR represents the number of the current record.
# For instance below example prints first two records
echo -e "One Two\nOne Two Three\nOne Two Three Four\n one" | awk 'NR < 3'
# RLENGTH represents the length of the string matched by match function. AWK's match function searches for a given string in the input-string.
awk 'BEGIN { if (match("One Two Three", "One ")) { print RLENGTH } }'           # 4
# RSTART represents the first position in the string matched by match function.
awk 'BEGIN { if (match("One Two Three", "Thre")) { print RSTART } }'            # 9
# $0 represents the entire input record.
awk '{print $0}' score.txt
# $n represents nth field in current record where fields are separated by FS.
awk '{print $3 "\t" $4}' score.txt
# IGNORECASE When this variable is set GAWK becomes case insensitive.
awk 'BEGIN{IGNORECASE=1} /amit/' score.txt
