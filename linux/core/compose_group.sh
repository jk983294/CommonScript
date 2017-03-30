#!/bin/bash

# composing
cmd1 ; cmd2 ; cmd3                      # sequential execution
cmd1 & cmd2 & cmd3                      # parallel execution
cmd1 && cmd2 && cmd3                    # conjunctive execution, if previous command return 0(OK), execute next command
cmd1 || cmd2 || cmd3                    # disjunctive execution, if previous command return non zero(failed), try next command

# grouping
(date; ls -l) > /tmp/a.txt              # capture output from both cmd
(sleep 10; echo DONE) &                # group cmd for background
