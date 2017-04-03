#!/bin/bash

grep ERROR data.txt                                                             # show ERROR lines
awk -F"|" '{ if($4 ~/ERROR/) print $0}' data.txt
grep -n ERROR data.txt                                                          # show ERROR lines with original row number
grep -c ERROR data.txt                                                          # get how many error lines

sort -k6 -n -t"|" data.txt                                                      # sort by column 6 numerically
sort -k5 -t"|" data.txt                                                         # sort by column 5
sort -k6 -nr -t"|" data.txt | head -5                                           # show top 5 max of column 6

# distinct
cut -f2 -d"|" data.txt | uniq                                                   # get distinct of column 2
awk -F"|" -f distinct.awk data.txt
awk -F"|" '{ if($4 ~/ERROR/){ a[$2]++ } } END{ for(record in a){ printf "%s show %d times\n", record, a[record] } }' data.txt
cut -f2 -d"|" data.txt | uniq | wc -l                                           # get how many distinct of column 2
awk '!($0 in array) { array[$0]; print }' data.txt                              # remove duplicate lines

# aggregate
awk -F"|" -f aggregate_number.awk data.txt                                      # F[2] = sigma (F[6]) if F[4] is ERROR; x.y1.z = 183
awk -F"|" 'function trim(str){ sub(/^[ \t\r\n]+/,"",str); sub(/[ \t\r\n]+$/,"", str);return str}
{ if($4 ~/ERROR/){ split(trim($2), arr, "."); a[arr[1]] = a[arr[1]] + $6 } }
END{ for(record in a){ printf "%s = %d\n", record, a[record] } }' data.txt      # F[2][1] = sigma (F[6]) if F[4] is ERROR; x1 = 148
awk -F"|" -f aggregate_text.awk data.txt                                        # F[2] = distinct(sigma (F[5])) if F[4] is ERROR; x.y1.z  = j,k,m,

# get max occurrence
awk -F"|" -f max_occurrence.awk data.txt

# reverse the order of lines in a file
awk '{ a[i++] = $0 } END { for (j=i-1;j>=0;j--) print a[j] }' data.txt


# reform
cat data.txt | cut -d"|" -f4 | paste - - - -                                    # get cloumn 4 and rearrange to four columns
