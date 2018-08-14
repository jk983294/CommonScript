# look up order:
#   1) current folder
#   2) "-I" or "--include-dir" folder
#   3) /usr/gnu/include
#   4) /usr/local/include
#   5) /usr/include
# if file not found, No such file or directory error reported
include /file/path

# replacement of include, it will ignore file not found error and continue
-include /file/path

# GNU version -include
sinclude /file/path
