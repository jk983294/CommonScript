#!/bin/bash

# i                                         insert
# a                                         append
# c                                         change
# d                                         delete
# p                                         print
# w file                                    write to file
# r file                                    read from file
# s/RE/RS/                                  substitute RE for RS once
# s/RE/RS/g                                 substitute RE for RS globally
# t addr                                    transfer to addr
# q                                         quit
# Q                                         really quit

# 1,$p                                      print from first line to last line
# 3i                                        insert in line 3
# /pattern1/,/pattern2/d                    delete lines match two patterns
# 3,$w tmp.txt                              write from line 3 to last line to tmp.txt
# /dpm/r tmp.txt                            read tmp.txt content under dpm line
# 2,3t$                                     copy line 2 and 3 to the end of file
# 1,$s/G/Greg                               substitute G for Greg globally
# g/Greg/p                                  print all lines match Greg
