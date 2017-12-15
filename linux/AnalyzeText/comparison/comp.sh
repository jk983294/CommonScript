#!/bin/bash

f1="a.txt"
f2="b.txt"
symbol="abc"
echo "Comparing | $f1 ${symbol} <-> $f2 ${symbol} | @$(date)"

{
eval $(
    echo -n "cat"
    echo -n " <(cat $f1 | sed -n '/summary:/,\$p' | awk '\$1 ~ /[[:digit:]]+/{ print \"$f1 ${symbol} \"\$2\" \"\$3 }')"
    echo -n " <(cat $f2 | sed -n '/summary:/,\$p' | awk '\$1 ~ /[[:digit:]]+/{ print \"$f2 ${symbol} \"\$2\" \"\$3 }')"
)
} |
awk -v s1=$f1 -v s2=$f2 '
$1==s1{ d1[$2" "$3]=$4 };
$1==s2{ d2[$2" "$3]=$4 };
END{
    for(k in d1) {
        printf k;
        if (k in d2){
            printf " | " (length(d1[k]) ? d1[k] : "*blank*") " <-> " (length(d2[k]) ? d2[k] : "*blank*") " | "
            if(!length(d1[k]) && !length(d2[k])){ /* all blank */
                print "_ OK";
            } else {
                if( (d1[k] ~ /^-?[[:digit:]\.]+$/) && (d2[k] ~ /^-?[[:digit:]\.]+$/) ){ /* num comp */
                    diff="echo \"(" d1[k] ") - (" d2[k] ")\" | bc "
                    diff | getline r;
                    close(diff)
                    printf r
                    gsub("^-", "", r)
                    comp="echo \"" r " < 0.001\" | bc"
                    comp | getline r;
                    close(comp)
                    print (r == "1") ? " OK" : " ERR"
                } else {
                    if ((d1[k] == d2[k]) && (d1[k] != "*ERR*") && (d2[k] != "*ERR*")) print "_ OK";
                    else print "_ ERR";
                }
            }
            delete d2[k]
        }else{
            print " | "(length(d1[k])?d1[k]:"*blank*")" <-> *missing* | _ ERR";
        }
    }
    for(k in d2) {
        print k" | *missing* <-> "(length(d2[k])?d2[k]:"*blank*")" | _ ERR";
    }
}'
