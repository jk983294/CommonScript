#!/bin/bash

# print shared object dependencies

ldd ./a.out | grep boost
ldd ./a.out | grep pthread

# LIBRARY_PATH used for time compile time shared object dependencies finding (.so compile time)
# LD_LIBRARY_PATH used for run time shared object dependencies finding (.so execution time)
