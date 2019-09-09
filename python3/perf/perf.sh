#!/bin/bash

time python3 someprogram.py
python3 -m cProfile someprogram.py
python3 -m cProfile -s cumulative someprogram.py

pip install line_profiler
# -l flag indicates line-by-line
# -v flag indicates verbose output
kernprof -l -v line_profiler_usage.py

pip install memory_profiler
pip install psutil
python3 -m memory_profiler line_profiler_usage.py

pip install guppy
# track how many objects of each type (str, tuple, dict, etc) are created at each stage in your code
python3 -m memory_profiler guppy_usage.py