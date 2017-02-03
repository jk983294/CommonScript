#!/usr/bin/env bash

# internal variables
# \$n	                            ��ǰ��¼�ĵ�n���ֶΣ��ֶμ���FS�ָ�
# \$0	                            �����������¼
# ARGC	                            �����в�������Ŀ
# ARGIND	                        �������е�ǰ�ļ���λ��(��0��ʼ��)
# ARGV	                            ���������в���������
# CONVFMT	                        ����ת����ʽ(Ĭ��ֵΪ%.6g)ENVIRON����������������
# ERRNO	                            ���һ��ϵͳ���������
# FIELDWIDTHS	                    �ֶο���б�(�ÿո���ָ�)
# FILENAME	                        ��ǰ�ļ���
# FNR	                            ͬNR��������ڵ�ǰ�ļ�
# FS	                            �ֶηָ���(Ĭ�����κοո�)
# IGNORECASE	                    ���Ϊ�棬����к��Դ�Сд��ƥ��
# NF	                            ��ǰ��¼�е��ֶ���
# NR	                            ��ǰ��¼��
# OFMT	                            ���ֵ������ʽ(Ĭ��ֵ��%.6g)
# OFS	                            ����ֶηָ���(Ĭ��ֵ��һ���ո�)
# ORS	                            �����¼�ָ���(Ĭ��ֵ��һ�����з�)
# RLENGTH	                        ��match������ƥ����ַ����ĳ���
# RS	                            ��¼�ָ���(Ĭ����һ�����з�)
# RSTART	                        ��match������ƥ����ַ����ĵ�һ��λ��
# SUBSEP	                        �����±�ָ���(Ĭ��ֵ��/034)
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
# NR represents the number of the current record.
# For instance below example prints first two records
echo -e "One Two\nOne Two Three\nOne Two Three Four\n one" | awk 'NR < 3'
# RLENGTH represents the length of the string matched by match function. AWK's match function searches for a given string in the input-string.
awk 'BEGIN { if (match("One Two Three", "One ")) { print RLENGTH } }'
# RSTART represents the first position in the string matched by match function.
awk 'BEGIN { if (match("One Two Three", "Thre")) { print RSTART } }'
# $0 represents the entire input record.
awk '{print $0}' score.txt
# $n represents nth field in current record where fields are separated by FS.
awk '{print $3 "\t" $4}' score.txt
# IGNORECASE When this variable is set GAWK becomes case insensitive.
awk 'BEGIN{IGNORECASE=1} /amit/' score.txt

# Arrays
awk 'BEGIN { arr[0] = 1; arr[1] = 2; arr[2] = 3; for (i in arr) printf "arr[%d] = %d\n", i, arr[i] }'
awk 'BEGIN { fruits["mango"]="yellow"; fruits["orange"]="orange"; print fruits["orange"] "\n" fruits["mango"]}'
awk 'BEGIN { fruits["mango"]="yellow"; fruits["orange"]="orange"; delete fruits["orange"]; print fruits["orange"]}'
awk 'BEGIN { array["0,0"] = 100; array["0,1"] = 200; array["1,0"] = 400; array["1,1"] = 500; print "array[0,0] = " array["0,0"]; }'