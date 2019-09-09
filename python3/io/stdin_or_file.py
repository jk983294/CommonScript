#!/opt/anaconda3/bin/python3

import fileinput

with fileinput.input() as f_input:
    for line in f_input:
        print(line, end='')

# ls | ./stdin_or_file.py               # Prints a directory listing to stdout.
# ./stdin_or_file.py /etc/passwd        # Reads /etc/passwd to stdout.
# ./stdin_or_file.py < /etc/passwd      # Reads /etc/passwd to stdout.
