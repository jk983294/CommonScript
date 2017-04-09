#!/bin/bash

sed 's/RE/RS/' afile                            # substitute RE for RS once
sed 's/RE/RS/2' afile                           # substitute RE for RS only for second occurrence of RE
sed 's/RE/RS/g' afile                           # substitute RE for RS globally

sed -n 's/RE/RS/p' afile                        # substitute RE for RS, and print

sed 's/RE/RS/w outfile' afile                   # substitute RE for RS, write those match lines to outfile

sed 's!/bin/bash!/bin/csh!' /etc/passwd         # use ! for seporator, default is /

sed 's/4.2/"&"/' afile                          # & is the matched content including wildcards
sed 's/\(45\)2/"\1"2/' afile                    # \n is the n-th sub-pattern
