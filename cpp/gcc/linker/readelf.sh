#!/bin/bash

# display ELF header
readelf -h /bin/ls

# displays the section headers
readelf -S /bin/ls
readelf -S a.out | grep debug      # check if compiled with -g

# displays section groups
readelf -g /bin/ls

# displays the detailed section information
readelf -t /bin/ls

# displays symbol table
readelf -s /bin/ls
# displays dynamic symbol table
readelf --dyn-syms /bin/ls


readelf -r /bin/ls          # display relocation section
readelf -n /bin/ls          # display note section
readelf -u /bin/ls          # display unwind section
readelf -d /bin/ls          # display dynamic section
readelf -V /bin/ls          # display version section

# display all, equivalent to --file-header, --program-headers, --sections, --symbols, --relocs, --dynamic, --notes and --version-info
readelf -a /bin/ls