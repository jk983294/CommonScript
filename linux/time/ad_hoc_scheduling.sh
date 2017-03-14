#!/bin/bash

at 11 am june 26
at noon tomorrow
# enter command line by line
# ctrl + d to end job definition

atq                                         # list jobs
atrm 3                                      # remove job 3

# batch takes you to at prompt and job will run when load average < 0.8
batch
