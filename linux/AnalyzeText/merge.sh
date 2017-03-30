#!/bin/bash

paste file1 file2                                   # merge column with tab
paste -d" " file1 file2                             # merge with space

cat afile | cut -d" " -f1 | paste - - -             # get cloumn 1 and then rearrange to three columns
