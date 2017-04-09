#!/bin/bash

# transform is the only command which can manipulate single character
# transform command is by default global transform
sed 'y/123/789/' data.txt                           # transform 1 -> 7, 2 -> 8, 3 -> 9
