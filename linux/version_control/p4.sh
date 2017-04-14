#!/bin/bash

p4 edit file1                                           # open file in a client workspace for edit.
p4 add file1
p4 delete file1
p4 move file1.c file2.c

p4 status                                               # previews output of open files for add, delete, and/or edit in order to reconcile a workspace with changes made outside of Perforce.

p4 diff file#5                                          # compare client revision file to server file revision 5.
p4 diff2 file#5 file#4                                  # compare file version 5 against version 4

p4 revert file1                                         # discard changes made to open file
p4 revert -a                                            # revert all unchanged files. This command is often used before submitting a changelist.

p4 change                                               # Create a new changelist.
p4 change -d 29                                         # Delete changelist 29. This succeeds only if changelist 29 is pending and contains no files.

p4 submit                                               # submit the default changelist.
p4 submit -c 41                                         # submit changelist 41.
p4 submit *.txt                                         # submit only .txt files in the default changelist. Move all the other files in the default changelist to the next default changelist.

p4 changes -m 5 //depot/project/...                     # last 5 changelist for this project
p4 describe                                             # displays the details on the default changelist
p4 opened -a -c default                                 # list all opened files in the default changelists for all client workspaces.
p4 opened -c 35 //depot/main/...                        # list all files in pending changelist 35 that lie under the depot’s main subdirectory.
p4 filelog file1                                        # print detailed information about files' revisions
