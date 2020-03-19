# determine what processes or users are currently accessing certain files
fuser -v /path/to/target_file
fuser -k /path/to/target_file           # terminate processes accessing the file