#!/bin/bash

# display file header contents
objdump -f /bin/ls

# display object format specific file header contents
objdump -p /bin/ls

# display contents of section headers
objdump -h /bin/ls

# display all headers
objdump -x /bin/ls

# display assembler contents of executable sections, --disassemble
objdump -d /bin/ls
objdump -D /bin/ls                      # like -d, but disassemble sections without instructions also
objdump -D --prefix-addresses /bin/ls   # prints the complete address on each line

# display the full contents, default to all section
objdump -s /bin/ls
objdump -s -j.rodata /bin/ls

# display debug information
objdump -g /bin/ls

# display contents of symbol table
objdump -t /bin/ls

# display the contents of dynamic symbol table which are resolved during run time
objdump -T /bin/ls
objdump -T /bin/ls | grep printf

# display the dynamic relocation entries
objdump -R /bin/ls
objdump -R /bin/ls | grep printf

# print the relocation entries of the file
# if used with -d or -D, the relocations are printed interspersed with the disassembly.
objdump -r /bin/ls
objdump -dr /bin/ls