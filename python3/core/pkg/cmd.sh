#!/bin/bash

# add current directory into PYTHONPATH variable
PYTHONPATH=. python3
PYTHONPATH=. python3 script.py

# or put .pth file under /opt/anaconda3/lib/python3.5/site-packages/

# or change sys.path

# install user python lib without root perm
# it install under ~/.local/lib/python3.3/site-packages
python3 setup.py install --user
pip install --user packagename

