#!/bin/bash

# open python interpreter after program finish to check variable
python3 -i sample.py

>>> import pdb
>>> pdb.pm()

# then you get gdb like debug tool
(Pdb) l
(Pdb) p n
