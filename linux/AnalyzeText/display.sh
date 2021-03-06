#!/bin/bash

# column format
mount | column -t

# cat & tac
cat file1 file2                                     # concatenate several files' content
cat file3                                           # display from  top to bottom
tac file3                                           # display from bottom to top
cat -vet file3                                      # show invisible character, $ for new line character, ^M$ for new line of windows file
cat -n file1                                        # add line number
cat -b file1                                        # only not empty line has line number
cat -T file1                                        # show tab as ^I

# head & tail
head /etc/passwd                                    # default first 10 lines
tail /etc/passwd                                    # default last 10 lines

head -n 3 /etc/passwd                               # show first 3 line
head -3 /etc/passwd

tail -n 1 /etc/passwd                               # show last line
tail -n +2 file.csv                                 # skip first 1 line, index base is 1, often used to skip header of csv file
tail -1 /etc/passwd
tail -f /var/log/message                            # leave the log file open, continue to watch last 10 lines in log file, Ctrl + C to leave

head -10 afile | tail -1                            # only show exactly 10th line


# more can only page down large file
# space     page down
# q         quit
more /etc/services

# less can page down and up file, even search content
# space / page down     page down
# page up               page up
# 16G                   go to 16th line
# /http                 search for http string
# n                     go to next occurrence of http string
# q                     quit
# v                     editor mode, editor specified by $EDITOR
# -i                    search ignore case
# Alt + u               un-highlight last search, it is a toggle
less /etc/services
ls -l /etc | less

# non-text files, never hard-code password
strings /bin/ls                                     # print the strings of printable characters in files

# octal dump, used to check un-printable character
cat a.txt
od a.txt
od -x a.txt                                         # display in hexadecimal
od -c a.txt                                         # display printable character where possible
od -d a.txt                                         # display in decimal

# nl show line number
nl list.txt
nl -w4 text.txt                                     # number width
nl -nln text.txt                                    # left align
nl -nrn sort.txt                                    # right align
nl -nrz text.txt                                    # right align, 0 padding
