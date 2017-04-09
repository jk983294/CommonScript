#!/bin/bash

# change match line to given line
sed '3c\to be changed' data.txt                             # change line 3
sed '/line match/c\to be changed' data.txt                  # change lines match /line match/
