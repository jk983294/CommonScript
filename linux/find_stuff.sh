#!/usr/bin/env bash

# Finding all files containing a text string
grep -rnw '/path/to/somewhere/' -e "pattern"
grep --include=\*.{c,h} -rnw '/path/to/somewhere/' -e "pattern"
grep --exclude=*.o -rnw '/path/to/somewhere/' -e "pattern"
grep --exclude-dir={dir1,dir2,*.dst} -rnw '/path/to/somewhere/' -e "pattern"
grep -ril "text-to-find-here" /
grep "pattern" ~/*.txt
grep "pattern" /home/jk/*.txt
grep --color -r "pattern" /home/jk/
# Only display filenames
grep -H -r "pattern" /home/jk
grep -H -r "pattern" /home/jk | cut -d: -f1

# find files by text in the file (find + grep)
find . -type f -name "*.txt" -exec grep -l Shyam {} \;              # find StringBuffer in all *.java files
find . -type f -name "*.java" -exec grep -l StringBuffer {} \;      # find StringBuffer in all *.java files
find . -type f -name "*.java" -exec grep -il string {} \;         	# ignore case with -i option
find . -type f -name "*.gz" -exec zgrep 'GET /foo' {} \;          	# search for a string in gzip'd files

# Find
find / -name foo.txt -type f -print             	    # full command
find . -name foo.txt                            		# search under the current dir
find . -name "foo.*"                            		# wildcard
find . -name "*.txt"                            		# wildcard
find /users/al -name Cookbook -type d	                # search '/users/al'

# search multiple dirs
find /opt /usr /var -name foo.scala -type f     # search multiple dirs

#case-insensitive searching
find . -iname foo                               # find foo, Foo, FOo, FOO, etc.
find . -iname foo -type d                       # same thing, but only dirs
find . -iname foo -type f                       # same thing, but only files

# find files with different extensions
find . -type f \( -name "*.c" -o -name "*.sh" \)                       # *.c and *.sh files
find . -type f \( -name "*cache" -o -name "*xml" -o -name "*html" \)   # three patterns

# find files that don't match a pattern (-not)
find . -type f -not -name "*.html"                                      # find all files not ending in ".html"

# 5 lines before, 10 lines after grep matches
find . -type f -name "*.scala" -exec grep -B5 -A10 'null' {} \;

# find files and act on them (find + exec)
find /usr/local -name "*.html" -type f -exec chmod 644 {} \;      		# change html files to mode 644
find htdocs cgi-bin -name "*.cgi" -type f -exec chmod 755 {} \;   	    # change cgi files to mode 755
find . -name "*.pl" -exec ls -ld {} \; 							        # run ls command on files found

# find and copy
find . -type f -name "*.mp3" -exec cp {} /tmp/MusicFiles \;       # cp *.mp3 files to /tmp/MusicFiles

# copy one file to many dirs
find dir1 dir2 dir3 dir4 -type d -exec cp header.shtml {} \;      # copy the file header.shtml to those dirs

#find and delete
find . -type f -name "Foo*" -exec rm {} \;                        # remove all "Foo*" files under current dir
find . -type d -name CVS -exec rm -r {} \;                        # remove all subdirectories named "CVS" under current dir

#find files by modification time
find . -mtime 1               # 24 hours
find . -mtime -7              # last 7 days
find . -mtime -7 -type f      # just files
find . -mtime -7 -type d      # just dirs

# find and tar
find . -type f -name "*.java" | xargs tar cvf myfile.tar
find . -type f -name "*.java" | xargs tar rvf myfile.tar

# find, tar, and xargs
find . -name -type f '*.mp3' -mtime -180 -print0 | xargs -0 tar rvf music.tar

# find and pax (instead of xargs and tar)
find . -type f -name "*html" | xargs tar cvf jw-htmlfiles.tar -
find . -type f -name "*html" | pax -w -f jw-htmlfiles.tar
