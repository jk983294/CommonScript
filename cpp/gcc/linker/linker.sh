#!/bin/bash

# linker script
g++ -o /dev/null -x c /dev/null -Wl,--verbose  | less
