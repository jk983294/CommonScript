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
awk -F"|" '{ if($4 ~/ERROR/){ a[$2]++ } } END{ for(record in a){ printf "%s show %d times\n", record, a[record] } }' data.txt
cut -f2 -d"|" data.txt | uniq | wc -l                                           # get how many distinct of column 2

# aggregate
awk -F"|" '{ if($4 ~/ERROR/){ a[$2] = a[$2] + $6 } }
END{ for(record in a){ printf "%s = %d\n", record, a[record] } }' data.txt      # F[2] = sigma (F[6]) if F[4] is ERROR; x.y1.z = 183
awk -F"|" 'function trim(str){ sub(/^[ \t\r\n]+/,"",str); sub(/[ \t\r\n]+$/,"", str);return str}
{ if($4 ~/ERROR/){ split(trim($2), arr, "."); a[arr[1]] = a[arr[1]] + $6 } }
END{ for(record in a){ printf "%s = %d\n", record, a[record] } }' data.txt      # F[2][1] = sigma (F[6]) if F[4] is ERROR; x1 = 148
awk -F"|" 'function trim(str){ sub(/^[ \t\r\n]+/,"",str); sub(/[ \t\r\n]+$/,"", str);return str}
{ if($4 ~/ERROR/){ split(trim($5), arr, ","); for(i in arr){ if(! match(a[$2],arr[i])){ a[$2] = a[$2] arr[i] "," } } } }
END{ for(record in a){ printf "%s = %s\n", record, a[record] } }' data.txt      # F[2] = distinct(sigma (F[5])) if F[4] is ERROR; x.y1.z  = j,k,m,

# reform
cat data.txt | cut -d"|" -f4 | paste - - - -                                    # get cloumn 4 and rearrange to four columns
